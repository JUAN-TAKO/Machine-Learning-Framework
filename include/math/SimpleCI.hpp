#include "../core/ComputationInterface.hpp"
class SimpleCI : public ComputationInterface{
public:
    static Tensor& add(Tensor& a, Tensor& b){
        unsigned int md = std::min(a.getDims(), b.getDims());
        std::vector<unsigned int> ms(md);
        for(int i(0); i < md; i++){
            ms[i] = std::min(a.getSize(i), b.getSize(i));
        }
        Tensor r(ms);
        for(int i(0); i < md; i++){
            for(int j(0); j < ms[i]; j++){
                r[j]
            }
        }
    }
    static Tensor& sub(Tensor& a, Tensor& b){

    }
    static Tensor& mult(Tensor& a, Tensor& b){

    }
    static Tensor& fill(Tensor& a, float val){
        for(auto i : a.getData()){
            i = val;
        }
    }
    static Tensor& exp(Tensor& a) = 0;
};