#pragma once

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <algorithm>
#include <functional>



template< typename NodeType>
class GraphNode
{
private:
    NodeType* m_Node;

    // Queue to be visited while traversing a graph
    //NodesQueue m_NodesQueue2Visit;
    std::deque<GraphNode*> m_NodesQueue2Visit;
    std::stack<GraphNode*> m_NodesStack2Visit;

    // Siblings
    std::list< GraphNode*> m_Siblings;

    std::vector< std::vector< GraphNode*>> m_AllDFSPaths;
    std::vector< std::vector< GraphNode*>> m_AllSolutionPaths;

    bool m_Flag = false;
    int m_Row = -1, m_Col = -1;
    int m_Rows = -1, m_Cols = -1;

    GraphNode* m_PrevGraphNode = nullptr;
    std::optional<int> m_FF; // measure from source
    std::optional<int> m_HH; // Heuristic value, measure from target
    std::optional<int> m_EvaluatedValue; // m_FF + m_HH
    std::optional<int> m_Value = 0;

public:

    GraphNode() = delete;
    GraphNode(const GraphNode& rhs):
        m_NodesQueue2Visit(rhs.m_NodesQueue2Visit),
        m_NodesStack2Visit(rhs.m_NodesStack2Visit),
        m_Siblings(rhs.m_Siblings),
        m_AllDFSPaths(rhs.m_AllDFSPaths),
        m_AllSolutionPaths(rhs.m_AllSolutionPaths),
        m_Flag(rhs.m_Flag),
        m_Row(rhs.m_Row),
        m_Col(rhs.m_Col),
        m_Rows(rhs.m_Rows),
        m_Cols(rhs.m_Cols),
        m_PrevGraphNode(rhs.m_PrevGraphNode),
        m_FF(rhs.m_FF),
        m_HH(rhs.m_HH),
        m_EvaluatedValue(rhs.m_EvaluatedValue),
        m_Value(rhs.m_Value)
    {

    }
    GraphNode(const int& val) :m_Value(val) {} // For testing purposes
    GraphNode(NodeType* nodeType, const int& row, const int& col, const int& tRows, const int& tCols) :
        m_Node(nodeType), m_Row(row), m_Col(col), m_Rows(tRows), m_Cols(tCols), m_Value(1) {}

    void SetPreviousNode(GraphNode* prevNode)
    {
        m_PrevGraphNode = prevNode;
    }
    bool isConnectedToSiblings(GraphNode* other)
    {
        auto finder = [&other](GraphNode* siblingNode)
        {
            if (siblingNode == other)
                return true;
            return false;
            
        };
        auto foundIter = std::find_if(this->m_Siblings.begin(), this->m_Siblings.end(), finder);
        if (foundIter != this->m_Siblings.end())
            return true;
        return false;
    }
    void add2VisitQueue(GraphNode* node)
    {
        m_NodesQueue2Visit.push(node);
    }
    void add2Siblings(GraphNode* node)
    {
        m_Siblings.push_back(node);
    }
    bool operator==(const GraphNode& rhs)
    {
        return (m_Row == rhs.m_Row && m_Col == rhs.m_Col);
    }
    bool operator!=(const GraphNode& rhs)
    {
        return !this->operator==(rhs);
    }
    void ComputeEvaluatedValue()
    {
        if (m_FF != std::nullopt && m_HH != std::nullopt)
        {
            m_EvaluatedValue = m_FF.value() + m_HH.value();
        }
        else
            m_EvaluatedValue = std::nullopt;
    }
    std::vector<GraphNode*> GetChildren()
    {
        std::vector<GraphNode*> res;
        std::for_each(m_Siblings.begin(), m_Siblings.end(), [&res](GraphNode* item)
            {
                res.push_back(item);
            });
        return res;
    }
    // The caller has to call the following function on each graphNode
    void setMeasureFromSource2Neighbors()
    {
        std::for_each(m_Siblings.begin(), m_Siblings.end(), [this](GraphNode* neighborNode)
            {
                /*gNode->setHH(heuristicValue);*/
                // Get the edge weight of the edge this 2 gNode (future)
                //if (this->m_FF == std::nullopt)
                  //  return;

                if (neighborNode->m_FF == std::nullopt )
                {
                    neighborNode->m_FF = this->m_FF.value() + 1 /*Edge weight*/;
                    neighborNode->m_PrevGraphNode = this;
                }
                else if (neighborNode->m_FF.value() > this->m_FF.value() + 1/*Edge Weight*/)
                {
                    neighborNode->m_FF = this->m_FF.value() + 1 /*Edge weight*/;
                    neighborNode->m_PrevGraphNode = this;
                }
                
                if (neighborNode->m_HH != std::nullopt && neighborNode->m_FF != std::nullopt )
                    neighborNode->m_EvaluatedValue = neighborNode->m_FF.value() + neighborNode->m_HH.value();
                
            });
    }
    void setHeuristicValues2Siblings(const int& heuristicValue)
    {
        std::for_each(m_Siblings.begin(), m_Siblings.end(), [heuristicValue](GraphNode* gNode)
            {
                gNode->setHH(heuristicValue);
            });
    }

    void setMeasureFromSource2Siblings(const int& measureFromSourceValue)
    {
        std::for_each(m_Siblings.begin(), m_Siblings.end(), [measureFromSourceValue](GraphNode* gNode)
            {
                gNode->setFF(measureFromSourceValue);
            });
    }

    void resetMeasureFromSource2Siblings()
    {
        std::for_each(m_Siblings.begin(), m_Siblings.end(), [](GraphNode* gNode)
            {
                gNode->resetFF();
            });
    }
    NodeType* getNode() { return m_Node; }
    bool flag() { return m_Flag; }
    void setFlag() { m_Flag = true; }
    void resetFlag() { m_Flag = false; }
    int getRow() const { return m_Row; }
    int getCol() const { return m_Col; }

    std::optional<int> getEvaluatedValue() { return m_EvaluatedValue; } // m_FF + m_HH


    void setMeasureFromSource(const int& ff) { m_FF = ff; }

    /*void setMeasureFromSource(const int& ff) { 
        if (m_FF == std::nullopt )
            m_FF = ff;
        else
        {
            if (ff < m_FF)
                m_FF = ff;
        }
        if (m_HH != std::nullopt )
            m_EvaluatedValue = m_FF.value() + m_HH.value();
    }*/
    bool isSibling(GraphNode* other)
    {   
        auto isSame = [&other](GraphNode* siblingNode)
        {
            if (siblingNode == other)
                return true;
            return false;
            
        };
        auto iter = std::find_if(m_Siblings.begin(), m_Siblings.end(), isSame);
        if (iter != m_Siblings.end())
            return true;
        return false;
    }
    void resetFF()
    {
        m_FF = std::nullopt;
        m_EvaluatedValue = std::nullopt;
    }
    void resetHH()
    {
        m_FF = std::nullopt;
        m_EvaluatedValue = std::nullopt;
    }
    void setFF(const int& ff) {
        if (m_FF == std::nullopt)
            m_FF = ff;
        else
        {
            if (ff < m_FF)
                m_FF = ff;
        }
        if (m_HH != std::nullopt)
            m_EvaluatedValue = m_FF.value() + m_HH.value();
    }

    std::optional<int> measureFromSource() { return m_FF; }
    std::optional<int> getFF() { return m_FF; }

    void setHeuristicValue(const unsigned int& hh)
    { 
        if (m_HH == std::nullopt)
            m_HH = hh;
        else
        {
            if (hh < m_HH)
                m_HH = hh;
        }
        if (m_FF != std::nullopt)
            m_EvaluatedValue = m_FF.value() + m_HH.value();
    }
    void setHH(const int& hh)
    { 
        if (m_HH == std::nullopt)
            m_HH = hh;
        else
        {
            if (hh < m_HH)
                m_HH = hh;
        }
        if (m_FF != std::nullopt)
            m_EvaluatedValue = m_FF.value() + m_HH.value();
    }
    
    std::optional<int> heuristic() { return m_HH; }
    
    std::optional<int> getHH() { return m_HH; }
    
    std::optional<int> value() { return m_Value; }
    void setValue(const int& val) { m_Value = val; }


    /*bool operator>(const GraphNode& rhs) { return m_EvaluatedValue.value() > rhs.m_EvaluatedValue.value(); }
    bool operator<(const GraphNode& rhs) { return m_EvaluatedValue.value() < rhs.m_EvaluatedValue.value(); }
    bool operator>=(const GraphNode& rhs) { return m_EvaluatedValue.value() >= rhs.m_EvaluatedValue.value(); }
    bool operator<=(const GraphNode& rhs) { return m_EvaluatedValue.value() <= rhs.m_EvaluatedValue.value(); }
    bool operator!=(const GraphNode& rhs) { return m_EvaluatedValue.value() != rhs.m_EvaluatedValue.value(); }
    bool operator==(const GraphNode& rhs) { return m_EvaluatedValue.value() == rhs.m_EvaluatedValue.value(); }*/

    void printElementAndChildren()
    {
        std::cout << " Node\t" << m_Row << "\t" << m_Col << "\t is connected with\t";
        std::for_each(m_Siblings.begin(), m_Siblings.end(),
            [](const GraphNode* neighborNode)
            {
                std::cout << "\t" << neighborNode->getRow() << "," << neighborNode->getCol() << "\t";
            });
        std::cout << std::endl;
    }

    void Print()
    {
        std::cout << "GRaphNode"<<std::endl;
        std::cout << m_Row << "," << m_Col << std::endl;
    }

    void BFS(std::optional<std::function<void(GraphNode*)>> visitor_fn_opt)
    {
        m_NodesQueue2Visit = std::deque<GraphNode*>();
        m_NodesQueue2Visit.push_back(this);

        while (m_NodesQueue2Visit.size() > 0)
        {
            auto& elem = m_NodesQueue2Visit.front();
            // Visit the node here
            //std::cout << "\nRow ->" << elem->m_Row << "\tCol ->" << elem->m_Col;
            if (visitor_fn_opt != std::nullopt)
            {
                auto visitor_fn = visitor_fn_opt.value();
                visitor_fn(elem);
            }
            elem->m_Flag = true;

            m_NodesQueue2Visit.pop_front();
            std::for_each(elem->m_Siblings.begin(), elem->m_Siblings.end(), [this](GraphNode*& item)
                {
                    if (!item->flag())
                        m_NodesQueue2Visit.push_back(item);
                });

        }
    }
    void PrintPaths()
    {
        std::for_each(m_AllSolutionPaths.begin(), m_AllSolutionPaths.end(), [](std::vector<GraphNode*>*& gnodeVec)
            {
                std::cout << "Path" << std::endl;
                std::for_each(gnodeVec.begin(), gnodeVec.end(), [](GraphNode*& gNode)
                    {
                        std::cout << "\t" << gNode->m_Row << "," << gNode->m_Col;
                    });
            });

    }
    std::vector< std::vector< GraphNode*>> DFS(std::optional<std::function<void(GraphNode*)>> visitor_fn_opt,
        std::function<std::vector<GraphNode*>(void)> graphNodesGetter)
    {
        m_NodesStack2Visit = std::stack<GraphNode*>();
        m_NodesStack2Visit.push(this);

        m_AllDFSPaths.clear();
        std::vector<GraphNode*> path;

        while (m_NodesStack2Visit.size() > 0)
        {

            auto& elem = m_NodesStack2Visit.top();
            {
                // Visit the node here
                if (visitor_fn_opt != std::nullopt)
                {
                    auto visitor_fun = visitor_fn_opt.value();
                    visitor_fun(elem);
                }
                path.push_back(elem);
                elem->m_Flag = true;
            }
            m_NodesStack2Visit.pop();


            // If elem has no siblings, it is the leaf node. Add it to the path
            bool pathAdded = false;
            bool leafNode = true;
            std::for_each(elem->m_Siblings.rbegin(), elem->m_Siblings.rend(), [&leafNode](GraphNode*& item)
                {
                    // Even if one unmarked node child exists, the current node is not leaf node.
                    if (!item->flag())
                        leafNode = false;
                });
            if (leafNode)
            {
                m_AllDFSPaths.push_back(path);
                pathAdded = true;
            }

            if (pathAdded)
            {
                pathAdded = false;
                leafNode = true;
                auto iter = path.rbegin();
                while (iter != path.rend())
                {
                    std::for_each((*iter)->m_Siblings.begin(), (*iter)->m_Siblings.end(),
                        [&leafNode](GraphNode*& pathSiblingItem)
                        {
                            if (!pathSiblingItem->flag())
                                leafNode = false;
                        });

                    if (leafNode)
                    {
                        std::advance(iter, 1);
                        path.erase(iter.base());
                        iter = path.rbegin();
                    }
                    else
                        break;
                };
            }


            // Reverse iterate the siblings list and push to the stack
            std::for_each(elem->m_Siblings.rbegin(), elem->m_Siblings.rend(), [this](GraphNode*& item)
                {
                    if (!item->flag())
                    {
                        m_NodesStack2Visit.push(item);
                    }
                });

        }

        return m_AllDFSPaths;
    }

    void printDFSMazeSolvePath()
    {
        std::for_each(m_AllSolutionPaths.begin(), m_AllSolutionPaths.end(), [](std::vector<GraphNode*>*& gnodeVec)
            {
                std::cout << "Path" << std::endl;
                std::for_each(gnodeVec.begin(), gnodeVec.end(), [](GraphNode*& gNode)
                    {
                        std::cout << "\t" << gNode->m_Row << "," << gNode->m_Col;
                    });
            });
    }
};