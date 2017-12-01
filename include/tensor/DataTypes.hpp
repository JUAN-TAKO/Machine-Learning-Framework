#include "Tensor.hpp"

using Vector<T> = Tensor<T, 1>;
using VectorI = Tensor<int, 1>;
using VectorF = Tensor<float, 1>;
using VectorD = Tensor<double, 1>;
using VectorB = Tensor<bool, 1>;

using Matrix<T> = Tensor<T, 2>;
using MatrixI = Tensor<int, 2>;
using MatrixF = Tensor<float, 2>;
using MatrixD = Tensor<double, 2>;
using MatrixB = Tensor<bool, 2>;

using Tensor3<T> = Tensor<T, 3>;
using Tensor3I = Tensor<int, 3>;
using Tensor3F = Tensor<float, 3>;
using Tensor3D = Tensor<double, 3>;
using Tensor3B = Tensor<bool, 3>;
