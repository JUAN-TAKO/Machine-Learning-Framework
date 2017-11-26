#include "../core/ComputationInterface.hpp"
class SimpleCI : public ComputationInterface{
public:
    static Tensor& add(Tensor& a, Tensor& b){
        unsigned int s = std::min(a.rawSize(), b.rawSize());
        unsigned int minDims = std::min(a.getDims(), b.getDims());
        std::vector<unsigned int> minSizes;
        for(int i(0); i < minDims; i++){
            minSizes.push_back(std::min(a.getSize(i), b.getSize(i)));
        }
        Tensor o(minSizes);
        for(int i = 0; i < s; i++){
            o.at(i) = a.at(i) + b.at(i);
        }
        return o;
    }
    static Tensor& sub(Tensor& a, Tensor& b){
        unsigned int s = std::min(a.rawSize(), b.rawSize());
        unsigned int minDims = std::min(a.getDims(), b.getDims());
        std::vector<unsigned int> minSizes;
        for(int i(0); i < minDims; i++){
            minSizes.push_back(std::min(a.getSize(i), b.getSize(i)));
        }
        Tensor o(minSizes);
        for(int i = 0; i < s; i++){
            o.at(i) = a.at(i) - b.at(i);
        }
        return o;
    }
    static Tensor& mult(Tensor& a, Tensor& b){

    }
    static Tensor& fill(Tensor& a, float val){
        for(auto i : a.getData()){
            i = val;
        }
    }
    static Tensor& exp(Tensor& a){
        
    }        
};