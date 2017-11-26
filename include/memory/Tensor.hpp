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


