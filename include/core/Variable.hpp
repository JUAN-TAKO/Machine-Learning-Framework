#pragma once
#include "Tensor.hpp"
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
    Variable(){ //this constructor should only be called by the user
        isRef = true;
        sharedPtr = std::make_shared(new _Variable());
    }
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

    Variable& operator=(Variable& v){
        isRef = true;
        if(v.isRef)
            sharedPtr = v.sharedPtr;
        else
            sharedPtr = v.weakPtr;
        
        return *this;
    }
    bool operator==(Variable& var1, Variable& var2){
        return var1.var==var2.var;
    }
    Variable getRef(){
        return Variable(*this, true);
    }
private:
    Variable(std::shared_ptr<Graph> o){  //this constructor will be used by the library internally
        isRef = false;
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
