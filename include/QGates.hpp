#ifndef Q_GATES_HPP
#define Q_GATES_HPP

#include "QTypes.hpp"
#include <iostream>
#include <vector>

namespace QCS 
{
    // Declare the Pauli Gates
    extern const CMatrix I;
    extern const CMatrix X;
    extern const CMatrix Y;
    extern const CMatrix Z;

    // Declare Rotation Gates
    CMatrix Rx(double theta);
    CMatrix Ry(double theta);
    CMatrix Rz(double theta);

    // Print the gate matrix
    void PrintGate(const CMatrix &gate);

    // Overloaded PrintGate for state vectors
    void PrintGate(const CVector &state);
}

#endif // Q_GATES_HPP

