#pragma once
#include <vector>
template<typename T>
class OSPair{
public:
    T offset;
    T size;
};

class TensorBase{
public:
    virtual std::array<float> getData() = 0;
    virtual Tensor operator[](unsigned int pos) = 0;
    virtual unsigned int getDims() = 0;
    virtual unsigned int getSize(unsigned int dim) = 0;
}

class Tensor : public TensorBase{
public:
    template<unsigned int...args>
    Tensor(unsigned int... args){
        sizes = {args};
        unsigned int s = 1;
        for(auto i : sizes){
            s *= i;
        }
        data = std::make_shared(new std::array(s));
    }
    Tensor(std::vector<unsigned int> s){
        sizes = s;
    }
    std::array<float> getData(){
        return *data;
    }
    Tensor operator[](unsigned int pos){
        int pos = 0;
        for(unsigned int i(0); i < sizes.size(); i++){
            pos += sizes[i] * a[i];
        }
        return getData()[pos];
    }
    unsigned int getDims(){
        return sizes.size();
    }
    unsigned int getSize(unsigned int dim){
        return sizes[dim];
    }

private:
    std::shared_ptr<std::array<float>> data;
    std::array<unsigned int> sizes;
};
class TensorView : public TensorBase{
public:
    std::shared_ptr<std::array<float>> data;
private:
    std::vector<OSPair<unsigned int>> view;
}


