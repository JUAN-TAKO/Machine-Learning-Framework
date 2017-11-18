#pragma once
#include "../memory/Tensor.hpp"
#include <cmath>

class Operation{
public:
    template<typename... Args>
    virtual Tensor operator()(Args.. args) = 0;
}

class OP_Add : Operation{
    Tensor operator()(Tensor& a, Tensor& b){
        return a.value() + b.value();
    }
}

class OP_Mult : Operation{
    Tensor operator()(Tensor& a, Tensor& b){
        return a.value() * b.value();
    }
}

class OP_Exp : Operation{
    Tensor operator()(Tensor& x){
        return std::exp(x.value());
    }
}