#pragma once
#include <queue>
#include <map>
#include <functional>



template< typename ElementType>
class MyPriorityQueue
{
private:
    std::priority_queue<ElementType*, std::vector<ElementType*>, std::function<bool(ElementType* left, ElementType* right)>> m_MinPQ;
    std::vector<ElementType*> m_Vec;
    std::function<bool(ElementType* left, ElementType* right)> m_MinCmpFunc;
public:
    MyPriorityQueue(std::function<bool(ElementType* left, ElementType* right)> cmp):m_MinCmpFunc(cmp)
    {   
        /*m_MinCmpFunc = [](ElementType* left, ElementType* right)
        {
            return (*left > *right);
        };*/

        m_MinPQ = std::priority_queue<ElementType*, std::vector<ElementType*>, std::function<bool(ElementType* left, ElementType* right)>>(m_MinCmpFunc);
    }
    ~MyPriorityQueue() {}

    bool Contains(ElementType* node)
    {
        auto iter = std::find_if(m_Vec.begin(), m_Vec.end(), [node](const ElementType* vecNode) {
            if (node == vecNode)
                return true;
            return false;
            });
        if (iter != m_Vec.end())
            return true;
        return false;
    }
    void Push(ElementType* node)
    {
        if (Contains(node))
            return;
        m_MinPQ.push(node);
        m_Vec.push_back(node);
    }

    void Push(ElementType* element, std::function<bool(ElementType* element)> predicate)
    {
        if (predicate(element))
            this->Push(element);
    }

    void Push(std::vector<ElementType*> nodes, std::function<bool(ElementType* element)> predicate)
    {
        std::for_each(nodes.begin(), nodes.end(), [this, &predicate](ElementType* element)
            {
                if (predicate(element))
                    this->Push(element);
            });
        
    }
    ElementType* Extract()
    {
        ElementType* elem = m_MinPQ.top();
        m_MinPQ.pop();
        
        // Remove the above elem from vector too.
        m_Vec.erase(std::remove(m_Vec.begin(), m_Vec.end(), elem), m_Vec.end());

        return elem;
    }

    ElementType* Peek()
    {
        ElementType* elem = m_MinPQ.top();
        return elem;
    }
    void printElements(std::vector<ElementType*>& vec)
    {
        std::for_each(vec.begin(), vec.end(), [](ElementType* item)
           {
               std::cout << "\t" << item->value().value();
           });
    }

    bool IsEmpty()
    {
        return (m_MinPQ.empty());
    }
    void printElements()
    {
        /*std::for_each(m_Vec.begin(), m_Vec.end(), [](ElementType* item)
            {
                std::cout << "\t" << item->value();
            });*/

        static ElementType* startElem = nullptr;
        std::vector<ElementType*> contents;


        
        while (!m_MinPQ.empty())
        {
            ElementType* elem = m_MinPQ.top();
            contents.push_back(elem);
            m_MinPQ.pop();
        } 

        std::for_each(contents.begin(), contents.end(), [this](ElementType* item)
            {
                this->m_MinPQ.push(item);
            });

        printElements(contents);
    }

    void Erase(ElementType* node, std::function<bool(ElementType* left, ElementType* right)> isEqual)
    {
        static ElementType* startElem= nullptr;
        std::vector<ElementType*> contents;

        while (!m_MinPQ.empty())
        {
            ElementType* elem = m_MinPQ.top();
            //if (*elem != *node)
            if ( !isEqual(elem, node))
                contents.push_back(elem);
            else
            {
                m_Vec.erase(std::remove(m_Vec.begin(), m_Vec.end(), elem), m_Vec.end());
            }
            m_MinPQ.pop();
        }
        /*ElementType* elem = m_MinPQ.top();
        do
        {
            if (!startElem)
                startElem = elem;

            if (elem && *elem != *node)
            {
                contents.push_back(elem);
            }
            else
            {
                m_Vec.erase(std::remove(m_Vec.begin(), m_Vec.end(), elem), m_Vec.end());
                break;
            }

            m_MinPQ.pop();
            elem = m_MinPQ.top();
        
        }while (*startElem != *elem);*/

        std::for_each(contents.begin(), contents.end(), [this](ElementType* item)
            {
                this->m_MinPQ.push(item);
            });
        
    }

    /*template <class Q>
    void Clear(Q& q) {
        q = Q();
    }*/

    void Clear()
    {
        while (!m_MinPQ.empty())
            m_MinPQ.pop();
        m_Vec.clear();
    }

    std::vector<ElementType*> GetElements()
    {
        return m_Vec;
    }
};
