#pragma once
#include "../tensor/Tensor.hpp"
#include "Graph.hpp"
#include <vector>
#include <memory>
#include "Operations.hpp"
/*
    class : Variable

*/
class Variable{
friend class Graph;
public:
    Variable(){
        isRef = false;
        sharedPtr = std::make_shared(new _Variable());
    }
    //copy. if getRef == true, the Variable created will not have any ownership of the graph
    Variable(Variable& v, bool getRef = false){
        if(getRef){
            isRef = false;
        }
        else{
            isRef = v.isRef;
        }
        if(isRef){
            if(v.isRef){
                weakPtr = v.sharedPtr;
            }
            else{
                weakPtr = v.weakPtr;
            }
        }
        else{
            if(v.isRef){
                sharedPtr = v.sharedPtr;
            }
            else{
                sharedPtr = v.weakPtr;
            }
        }
    }

    static Variable operator+(Variable& a, Variable& b){
        return ara::add(a, b); 
        //std::shared_ptr<Graph> g = findOwner(a,b);
        //return g.addOP(OP_Add(a, b));
    }
    
    static Variable operator*(Variable& a, Variable& b){
        return ara::multiply(a, b);
        //std::shared_ptr<Graph> g = findOwner(a,b)
        //return g.addOP(OP_Mult(a, b));
    }

    //should not be used by the library !
    //use set instead
    Variable& operator=(Variable& v){
        isRef = false;
        if(v.isRef)
            sharedPtr = v.sharedPtr;
        else
            sharedPtr = v.weakPtr;
        
        return *this;
    }

    Variable& operator=(Tensor& t){

    }
    bool operator==(Variable& var1, Variable& var2){
        return var1.var==var2.var;
    }
    Variable getRef(){
        return Variable(*this, true);
    }
private:
    Variable& set(Variable& v){
        isRef = true;
        if(v.isRef)
            weakPtr = v.sharedPtr;
        else
            weakPtr = v.weakPtr;
        
        return *this;
    }
    Variable(std::shared_ptr<Graph> o){
        isRef = true;
        weakPtr = std::make_shared(_Variable(o));
    }
    bool isRef;
    std::shared_ptr<_Var> sharedPtr;
    std::weak_ptr<_Var> weakPtr;
};
class _Variable{
friend class Variable;
private:
    _Variable(){
        data = std::make_shared(new Tensor());
        gradient = std::make_shared(new Tensor());
        owner = std::make_shared(new Graph());
    }
    _Variable(std::shared_ptr<Graph> o){
        data = std::make_shared(new Tensor());
        gradient = std::make_shared(new Tensor());
        owner = o;
    }
    std::shared_ptr<Tensor> data;
    std::shared_ptr<Tensor> gradient;
    std::shared_ptr<Graph> owner;
}
