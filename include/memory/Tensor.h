class _Tensor{
friend class Tensor;
private:

}

template<typename T>
class FTPair{
public:
    T from;
    T to;
}
class Tensor{
public:
    _Tensor& getData(){
        return data;
    }
private:
    _Tensor data;
    std::vector<FTPair<unsigned int>> view;
};