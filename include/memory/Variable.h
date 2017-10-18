#pragma once
#include "Tensor.h"
#include <vector>
#include <memory>
#include <ElementaryOperations.h>

class Variable{
friend class Graph;
public:
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

    Variable& operator=(Variable& var){
        data = var.data;
        owner = var.owner;
    }

    bool operator==(Variable& var1, Variable& var2){
        return var1==var2;
    }
private:
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
    
    std::shared_ptr<_Variable> var;
};
class _Variable{
friend class Variable;
private:
    std::shared_ptr<Tensor> data;
    std::shared_ptr<Tensor> gradient;
    //event ev;
    std::shared_ptr<Graph> owner;
    GraphOperation* gOp;
    unsigned int opIndex;
}