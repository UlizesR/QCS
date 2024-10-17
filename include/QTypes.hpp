#ifndef Q_TYPES_HPP
#define Q_TYPES_HPP

#include <Eigen3/Eigen/Dense>

namespace QCS
{
    using Complex = std::complex<double>;
    using CVector = Eigen::VectorXcd;
    using CMatrix = Eigen::MatrixXcd;
}

#endif // Q_TYPES_HPP
