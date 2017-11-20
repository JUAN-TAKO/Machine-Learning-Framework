#include "../memory/Tensor.hpp"

class ComputationInterface{
public:
    virtual Tensor& add(Tensor& a, Tensor& b) = 0;
    virtual Tensor& sub(Tensor& a, Tensor& b) = 0;
    virtual Tensor& mult(Tensor& a, Tensor& b) = 0;
    virtual Tensor& fill(Tensor& a, float val) = 0;
    virtual Tensor& exp(Tensor& a) = 0;

    //...
private:

};