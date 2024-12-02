#include "QState.hpp"
#include "QGates.hpp"

#include <iostream>
#include <cmath>    // For M_PI

int main()
{
    // Define pi
    const double pi = M_PI;

    // Print the Pauli gates
    std::cout << "Pauli Gates" << std::endl;
    
    std::cout << "I" << std::endl;
    QCS::PrintGate(QCS::I);
    
    std::cout << "X" << std::endl;
    QCS::PrintGate(QCS::X);
    
    std::cout << "Y" << std::endl;
    QCS::PrintGate(QCS::Y);
    
    std::cout << "Z" << std::endl;
    QCS::PrintGate(QCS::Z);
    
    // Print the rotation gates
    std::cout << "Rotation Gates" << std::endl;
    
    std::cout << "Rx(pi/2)" << std::endl;
    QCS::PrintGate(QCS::Rx(pi / 2));
    
    std::cout << "Ry(pi/2)" << std::endl;
    QCS::PrintGate(QCS::Ry(pi / 2));
    
    std::cout << "Rz(pi/2)" << std::endl;
    QCS::PrintGate(QCS::Rz(pi / 2));
    
    // Initialize QState with 3 qubits (example)
    QCS::QState qstate(3);
    
    // Apply Rx(pi/2) to qubit 0
    std::vector<int> x_axis = {0}; // Qubit indices are zero-based
    qstate.apply_gate(QCS::Rx(pi / 2), x_axis);
    std::cout << "After applying Rx(pi/2) to qubit 0:" << std::endl;
    qstate.display_state();
    
    // Measure qubit 0
    int result = qstate.measure(0);
    if(result != -1)
    {
        std::cout << "State after measurement:" << std::endl;
        qstate.display_state();
    }

    return 0;
}

