#pragma once
#include "Variable.hpp"
#include <cmath>

class Operation{
public:

    virtual std::unique_ptr<Operation> clone() = 0;
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
   OP_Add(std::vector<Variable> in) : inputs(in), outputs(1){}

    std::vector<Variable> operator()(){
        outputs[0] = inputs[0].value() + inputs[1].value();
        return outputs;
    }

    std::unique_ptr<Operation> clone(){
        return std::make_unique(new OP_Add(inputs));
    }

}

class OP_Mult : public Operation{
public:
   OP_Mult(std::vector<Variable> in) : inputs(in), outputs(1){}

    std::vector<Variable> operator()(){
        outputs[0] = inputs[0].value() * inputs[1].value();
        return outputs;
    }

    std::unique_ptr<Operation> clone(){
        return std::make_unique(new OP_Mult(inputs));
    }
}

class OP_Exp : public Operation{
public:
   OP_Exp(std::vector<Variable> in) : inputs(in), outputs(1){}

    std::vector<Variable> operator()(){
        outputs[0] = inputs[0].value().exp();
        return outputs;
    }

    std::unique_ptr<Operation> clone(){
        return std::make_unique(new OP_Exp(inputs));
    }
}