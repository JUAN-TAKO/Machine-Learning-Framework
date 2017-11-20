#pragma once
#include <vector>
#include "Variable.hpp"
#include "Operations.hpp"

class Graph{
public:
    Graph(){
        graph = std::make_shared(new _Graph());
    }

    template<typename Args>
    Variable addOP(Operation op, Args... args){
        std::vector<Variable> v = {args};
        auto opPtr = op.clone();

        graph->operations.push_back(opPtr);
        for(auto&& i : v){
            graph->fOp.insert(i, opPtr.get());
        }
        for(auto&& i : opPtr->getOutputs()){
            graph->bOp.insert(i, opPtr.get())
        }
    }
private:
    Graph(std::shared_ptr<_Graph> g){
        graph = g;
    }
    
    std::shared_ptr<_Graph> graph;

};
class _Graph{
friend class Graph;
private:

    std::vector<std::unique_ptr<Operation>> operations;
    std::map<Variable, Operation*> fOp;
    std::map<Variable, Operation*> bOp;
}

class Module : public Operation{
public:
    virtual Variable forward() = 0;
    template<typename... Args>
    virtual Variable operator()(Args... args){
        inputs = {args};
        return forward(args);
    }
    virtual void backward(Variable pb_for){
        
    }
    
private:
    std::shared_ptr<Graph> graph;
}