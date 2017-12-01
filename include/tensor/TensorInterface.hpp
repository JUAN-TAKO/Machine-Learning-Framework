#include <array>
class Tensor{
public:
    virtual std::array<float> getData() = 0;
    virtual Tensor operator[](size_t index) = 0;
    virtual size_t getDims() = 0;
    virtual size_t size() = 0;
}