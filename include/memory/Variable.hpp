#pragma once
#include "Tensor.hpp"
#include "../core/Graph.hpp"
#include <vector>
#include <memory>
#include "../math/ElementaryOperations.hpp"

class Variable{
friend class Graph;
public:
    Variable(){
        createdByUser = true;
        owner = std::make_shared(new Graph);
        var = std::make_shared(new _Variable(owner));
    }
    static Variable operator+(Variable& a, Variable& b){
        E_Add(a.data, b.data);
        std::shared_ptr<Graph> g = findOwner(a,b);
        auto r = g.addOP(a, b, ARA_OP_ADD);
        return r;
    }
    
    static Variable operator*(Variable& a, Variable& b){
        E_Mult(a.data, b.data);
        std::shared_ptr<Graph> g = findOwner(a,b);
        auto r = g.addOP(a, b, ARA_OP_MUL);
        return r;
    }

    Variable& operator=(Variable& v){
        createdByUser = true;
        var = v.var;
        owner = v.owner;
        if(!v.createdByUser){
            v.owner = nullptr;
        }
        
        return *this;
    }

    bool operator==(Variable& var1, Variable& var2){
        return var1.var==var2.var;
    }
private:
    Variable(std::shared_ptr<Graph> o){
        createdByUser = false;
        owner = nullptr;
        var = std::make_shared(_Variable(o));
    }
    /*
    std::shared_ptr<Graph> findOwner(Variable& a, Variable& b){
        std::shared_ptr<Graph> r;
        if(a.owner){
            r = a.owner;
            b.setOwner(r);
        }
        else if(b.owner){
            r = b.owner;
            a.setOwner(r);
        }
        else{
            r = std::make_shared(new Graph());
            a.setOwner(r);
            b.setOwner(r);
            return r;
        }
    }
    void setOwner(std::shared_ptr<Graph> newOwner){
        var->owner->mergeWith(newOwner)
    }
    void directSetOwner(std::shared_ptr<Graph> newOwner){
        var.owner = newOwner;
    }*/
    bool createdByUser;
    std::shared_ptr<Graph> owner;
    std::shared_ptr<_Variable> var;
};
class _Variable{
friend class Variable;
private:
    std::shared_ptr<Tensor> data;
    std::shared_ptr<Tensor> gradient;
    //event ev;
    std::weak_ptr<Graph> owner;
    GraphOperation* gOp;
    unsigned int opIndex;
}