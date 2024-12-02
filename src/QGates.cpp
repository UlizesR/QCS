#include "QGates.hpp"

namespace QCS 
{
    // Define the Pauli Gates
    const CMatrix I = CMatrix::Identity(2, 2);

    const CMatrix X = (CMatrix(2, 2) << 0, 1, 1, 0).finished();

    const CMatrix Y = (CMatrix(2, 2) << 0, Complex(0, -1), Complex(0, 1), 0).finished();

    const CMatrix Z = (CMatrix(2, 2) << 1, 0, 0, -1).finished();

    // Define Rotation Gates
    CMatrix Rx(double theta)
    {
        return (CMatrix(2, 2) 
            << std::cos(theta / 2), Complex(0, -1) * std::sin(theta / 2), 
               Complex(0, -1) * std::sin(theta / 2), std::cos(theta / 2))
            .finished();
    }

    CMatrix Ry(double theta)
    {
        return (CMatrix(2, 2) 
            << std::cos(theta / 2), -std::sin(theta / 2), 
               std::sin(theta / 2), std::cos(theta / 2))
            .finished();
    }

    CMatrix Rz(double theta)
    {
        return (CMatrix(2, 2) 
            << std::exp(Complex(0, -theta / 2)), 0, 
               0, std::exp(Complex(0, theta / 2)))
            .finished();
    }

    // Print the gate matrix
    void PrintGate(const CMatrix &gate)
    {
        std::cout << gate << std::endl;
    }

    // Overloaded PrintGate for state vectors
    void PrintGate(const CVector &state)
    {
        std::cout << state << std::endl;
    }
}
