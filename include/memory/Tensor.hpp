#pragma once
template<typename T>
class FTPair{
public:
    T from;
    T to;
};

class P_Tensor{
private:

};

class Tensor{
public:
    P_Tensor& getData(){
        return data;
    }
private:
    P_Tensor data;
    std::vector<FTPair<unsigned int>> view;
};


