#pragma once
#include <vector>

#include <ElementaryOperations.h>

class Graph{
public:
    void mergeWith(std::shared_ptr<Graph> g){
        for(auto i : operations){
            g->operations->push_back(i);    
        }
        //TODO : transfer links
        for(auto i : variables){
            i.var->owner = g;
        }
    }
    Variable addOP(Variable a, Variable b, unsigned int opCode){
        
    }
private:
    std::vector<Variable> variables;
    std::vector<std::shared_ptr<GraphOperation>> operations;

    std::map<Variable, std::vector<Variable>> fLinks;
    std::map<Variable, Variable> bLinks;

};


/*
class Node{
public:
    
private:
    GraphOperation* go;
    bool isInput;
    unsigned int index;
    Variable var;
};*/
class GraphOperation{
private:
    std::vector<Variable> in;
    std::vector<Variable> out;
    unsigned int opCode;
}
class Module{
public:
    virtual Variable forward() = 0;
    template<typename... Args>
    virtual Variable operator()(Args... args){
        return forward(args);
    }
    virtual void backward(Variable pb_for){
        
    }
    //Variable output

    Graph graph;
}