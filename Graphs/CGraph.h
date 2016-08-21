#pragma once

#include <vector>
#include <list>
#include <cassert>

template <typename T, typename M>
class CNode; // Вершина.

template <typename T, typename M>
class CEdge; // Ребро.

template <typename T, typename M>
class CEdge { // Ребро.
public:
    CEdge(CNode<T, M>* e, M w) :
            end(e), weight(w)
    {}
    virtual ~CEdge()
    {}
    CNode<T, M>* GetEnd() const
    {
        return end;
    };
    void SetEnd(CNode<T, M>* e)
    {
        end = e;
    }
    M GetWeight() const
    {
        return weight;
    }
    void SetWeight(M weight)
    {
        CEdge::weight = weight;
    }

protected:
    CNode<T, M>* end; // Куда входит.
    M weight; // Вес ребра.
};

template <typename T, typename M>
class CNode { // Вершина.
public:
    CNode(T val, size_t num) :
            value(val), number(num)
    {}
    virtual ~CNode()
    { }
    T GetValue() const
    {
        return value;
    }

    void SetValue(T value)
    {
        CNode::value = value;
    }

    size_t GetNumber() const
    {
        return number;
    }

    void SetNumber(size_t number)
    {
        CNode::number = number;
    }

    const std::list<CEdge<T, M>>& GetSuccessors() const
    {
        return successors;
    };

    void AddSuccessor(CEdge<T, M> edge) // Добавление вершины в список смежности.
    {
        successors.push_back(edge);
    }
protected:
    T value; // Значение, хранящееся в вершине.
    size_t number; // Номер вершины.
    std::list<CEdge<T, M>> successors; // Список смежности.
};

template <typename T, typename M>
class CGraph { // Граф.
public:
    CGraph() :
            default_weight(1), default_value(0), size(0) {}
    CGraph(M dw, T dv) :
            default_weight(dw), default_value(dv) {}
    virtual ~CGraph();
    virtual size_t AddVertex(T val); // Добавление вершины.
    virtual size_t AddVertex(CNode<T, M> *node);
    virtual size_t AddVertex();
    //virtual size_t AddVertex(T val, size_t number);
    virtual void AddDirectedEdge(int start, int end, M weight); // Добавление направленного ребра.
    virtual void AddDirectedEdge(int start, int end);
    virtual void AddUndirectedEdge(int start, int end, M weight); // Добавление ненаправленного ребра.
    virtual void AddUndirectedEdge(int start, int end);
    virtual T GetValue(size_t number) const; // Получение значениея в вершине по номеру.
    virtual const CNode<T, M>* GetNode(size_t number) const; // Получение вершины по номеру.
    size_t GetSize() const{ return size; } // Получение количества вершин в графе.
protected:

    std::vector<CNode<T, M>*> vertices; // Вектор вершин.
    size_t size; // Количество вершин в графе.
    const M default_weight; // Значение веса ребра по умолчанию.
    const T default_value; // Значение в вершине по умолчанию.
};

template <typename T, typename M>
size_t CGraph<T, M>::AddVertex(T val)
{
    CNode<T, M> *newnode = new CNode<T, M>(val, 0);
    return AddVertex(newnode);
}

template <typename T, typename M>
size_t CGraph<T, M>::AddVertex()
{
    return AddVertex(default_value);
}

/*template <typename T, typename M>
size_t CGraph<T, M>::AddVertex(T val, size_t number)
{
    CNode<T, M>* newnode = new CNode<T, M>(val, number);
    size++;
    if(number >= vertices.size()) {
        vertices.resize(number+1);
        vertices[number] = newnode;
    }
    else {
        if(vertices[number] == nullptr) {
            vertices[number] = newnode;
            if(cur_pos == number-1) {
                cur_pos++;
            }
        }
        else {
            CNode<T, M>* temp = vertices[number];
            vertices[number] = newnode;
            addVertex(temp);
        }
    }
    return number;
}*/

template <typename T, typename M>
size_t CGraph<T, M>::AddVertex(CNode<T, M> *node)
{
    node->SetNumber(size);
    vertices.push_back(node); // Вставляем вершину.
    size++;
    return size-1;
}

template <typename T, typename M>
void CGraph<T, M>::AddDirectedEdge(int start, int end, M weight)
{
    assert(start < vertices.size() && end < vertices.size()); // Проверяем, что такие вершины есть.

    vertices[start]->AddSuccessor(CEdge<T, M>(vertices[end], weight)); // Добавляем конечную вершину в список смежности.
}

template <typename T, typename M>
void CGraph<T, M>::AddDirectedEdge(int start, int end) {
    AddDirectedEdge(start, end, default_weight);
}

template <typename T, typename M>
T CGraph<T, M>::GetValue(size_t number) const
{
    assert(number < vertices.size());
    return vertices[number]->GetValue();
}

template <typename T, typename M>
void CGraph<T, M>::AddUndirectedEdge(int start, int end, M weight)
{
    AddDirectedEdge(start, end, weight); // Добавляем ребро в обе стороны.
    AddDirectedEdge(end, start, weight);
}

template <typename T, typename M>
void CGraph<T, M>::AddUndirectedEdge(int start, int end)
{
    AddUndirectedEdge(start, end, default_weight);
}

template <typename T, typename M>
const CNode<T, M>* CGraph<T, M>::GetNode(size_t number) const
{
    assert(number < vertices.size()); // Проверяем, что такая верштна с таки номерос есть.
    return vertices[number];
};

template <typename T, typename M>
CGraph<T, M>::~CGraph()
{
    for(int i = 0; i < vertices.size(); i++) { // Удаляем в цикле все вершины.
        delete vertices[i];
    }
}


