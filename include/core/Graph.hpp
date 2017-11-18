#pragma once
#include <vector>
#include "../memory/Variable.hpp"
#include "../math/ElementaryOperations.hpp"

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
    Variable addOP(Args.. args, unsigned int opCode){
        std::vector<Variable> v = {args};
        GraphOperation go(v, opCode);
        auto opPtr = std::make_shared(go);
        graph->operations.push_back(opPtr);
        for(auto&& i : v){
            graph->fOp.insert(i, opPtr);
        }
        for(auto&& i : opPtr->getOutputs()){
            graph->bOp.insert(i, opPtr)
        }
    }
private:
    std::shared_ptr<_Graph> graph;

};
class _Graph{
friend class Graph;
private:

    std::vector<std::shared_ptr<GraphOperation>> operations;
    std::map<Variable, std::shared_ptr<GraphOperation>> fOp;
    std::map<Variable, std::shared_ptr<GraphOperation>> bOp;
}

class GraphOperation{
public:
    std::vector<Variable> getInputs(){
        return in;
    }
    std::vector<Variable> getOutputs(){
        return out;
    }

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