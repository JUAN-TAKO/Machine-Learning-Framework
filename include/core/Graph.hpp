#pragma once
#include <vector>
#include "Variable.hpp"
#include "Operations.hpp"

class Graph{
public:
    std::shared_ptr<Graph> clear(){ //reset the graph and returns the old one
        auto s = graph;
        graph = std::make_shared(new _Graph());
        return std::make_shared(new Graph(s));
    }
    Graph(){
        graph = std::make_shared(new _Graph());
    }
    Graph(std::shared_ptr<_Graph> g){
        graph = g;
    }

    template<typename Args>
    Variable addOP(Operation op, Args... args){
        std::vector<Variable> v = {args};
        auto opPtr = op(v);

        graph->operations.push_back(opPtr);
        for(auto&& i : v){
            graph->fOp.insert(i, opPtr.get());
        }
        for(auto&& i : opPtr->getOutputs()){
            graph->bOp.insert(i, opPtr.get())
        }
    }
private:
    std::shared_ptr<_Graph> graph;

};
class _Graph{
friend class Graph;
private:

    std::vector<std::unique_ptr<Operation>> operations;
    std::map<Variable, Operation*> fOp;
    std::map<Variable, Operation*> bOp;
}

class Module{
public:
    virtual Variable forward() = 0;
    template<typename... Args>
    virtual Variable operator()(Args... args){
        inputs = args;
        return forward(args);
    }
    virtual void backward(Variable pb_for){
        
    }
    
    //Variable output
private:
    std::vector<Variable> inputs;
    std::vector<Variable> outputs;
    std::shared_ptr<Graph> graph;
}