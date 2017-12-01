#pragma once
#include "TensorInterface.h"
#include <vector>
#include <array>

class Tensor{
public:
    virtual void getData() = 0;
    virtual void at(size_t index) = 0;
    virtual size_t getDims() = 0;
    virtual size_t getSize(size_t dim) = 0;
    
    virtual Tensor& operator[](size_t index) = 0;
    virtual Tensor& operator[](size_t index, size_t length) = 0;
    virtual Tensor& operator[]() = 0;
    virtual Tensor& fill(Tensor& a, float val) = 0;

    virtual Tensor& add(Tensor& a, Tensor& b) = 0;
    virtual Tensor& sub(Tensor& a, Tensor& b) = 0;
    virtual Tensor& mult(Tensor& a, Tensor& b) = 0;
    virtual Tensor& div(Tensor& a, Tensor& b) = 0;

    virtual Tensor& dist(Tensor& a, Tensor& b) = 0;
    
    virtual Tensor& transform(std::function<Tensor&(Tensor&)> function) = 0;
    virtual Tensor& exp(Tensor& a) = 0;

}

template<typename T, int D>
class Tensor : public Tensor{
private:
    std::vector<Tensor<T, D-1>> data;
    size_t tSize;
    std::array<size_t> sizes;
    T* begin;
    T* end;
public:
    Tensor<T, D-1> operator[](size_t index){
        return data[index];
    }
    T at(size_t index){
        return begin[index];
    }
    size_t size(){
        return tSize;
    }
    size_t elements(){
        return data.size();
    }
    size_t elements_size(){
        return data[0].size();
    }
}


/*
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
        offset = 0;
        size = data->size()
    }
    Tensor(std::vector<unsigned int> s){
        sizes = s;
        unsigned int s = 1;
        for(auto i : sizes){
            s *= i;
        }
        data = std::make_shared(new std::array(s));
        offset = 0;
        size = data->size;
    }
    std::array<float> getData(){
        return *data;
    }
    Tensor operator[](unsigned int pos){
        auto t = TensorView(this, pos);
        return t[pos];
    }
    unsigned int getDims(){
        return sizes.size();
    }
    unsigned int getSize(unsigned int dim){
        return sizes[dim];
    }
    float* begin(){
        return offset;
    }
    float* end(){
        return offset + size;
    }
    unsigned int rawSize(){
        return size;
    }
    float& at(unsigned int index){
        return data[index + offset];
    }
private:
    
    Tensor(Tensor* t, unsigned int pos){
        int off = pos;
        int s = 1;
        sizes = std::array(t->sizes.size()-1);
        for(unsigned int i = 1; i < t->sizes.size(); i++){
            off *= i;
            s *= i;
            sizes[i-1] = t->sizes[i];
        }
        data = t->data;
        offset = o;
        size = s;
    }

    std::shared_ptr<std::array<float>> data;
    std::array<unsigned int> sizes;
    float* offset;
    unsigned int size; 
};
class TensorView : public TensorBase{
public:
    TensorView(Tensor t){
        data = std::make_shared(t.getData());

    }
    TensorView operator[](unsigned int pos){
    }
private:
    std::shared_ptr<std::array<float>> data;
    std::vector<OSPair<unsigned int>> view;
}

*/
