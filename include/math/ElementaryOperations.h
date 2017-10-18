#pragma once
#include "Tensor.h"
#include <cmath>

Tensor E_Add(Tensor& a, Tensor& b){
    return a.value() + b.value();
}


Tensor E_Mult(Tensor& a, Tensor& b){
    return a.value() * b.value();
}


Tensor E_Exp(Tensor& x){
    return std::exp(x.value());
}
