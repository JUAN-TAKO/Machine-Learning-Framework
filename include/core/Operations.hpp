#pragma once
#include "Variable.hpp"
#include <cmath>

class Operation{
public:
    Operation(std::vector<Variable> in) : inputs(in) {}

    virtual std::unique_ptr<Operation> operator()(std::vector<Variable> in) = 0;
    virtual std::vector<Variable> operator()() = 0;

    std::vector<Variable> getOutputs(){
        return outputs;
    }
    std::vector<Variable> getInputs(){
        return inputs;
    }

private:
    std::vector<Variable> inputs;
    std::vector<Variable> outputs;
}

class OP_Add : public Operation{
public:
    using Operation::Operation;

    std::vector<Variable> operator()(){
        outputs[0] = inputs[0].value() + inputs[1].value();
        return outputs;
    }
}

class OP_Mult : public Operation{
    std::vector<Variable> operator()(){
        outputs[0] = inputs[0].value() + inputs[1].value();
        return outputs;
    }
    std::unique_ptr<Operation> operator()(std::vector<Variable> in){
        outputs = std::vector<Variable>(1);
        return std::make_unique<Operation>(new OP_Add(in));
    }
}

class OP_Exp : public Operation{
    Tensor operator()(Tensor& x){
        return std::exp(x.value());
    }
}