#ifndef QUANTUM_STATE_HPP
#define QUANTUM_STATE_HPP

#include "QGates.hpp"
#include <vector>
#include <cstdint>
#include <random>
#include <stdexcept>

namespace QCS
{
    class QState
    {
    private:
        // Applies a single-qubit gate to the specified qubit
        void apply_single_qubit_gate(const CMatrix& gate, int qubit);

    public:
        uint8_t num_qubits;
        CVector state;

        // Constructor: initializes to |0...0>
        QState(uint8_t num_qubits_);

        // Apply a gate to specified target qubits
        void apply_gate(const CMatrix& gate, const std::vector<int>& target_qubits);

        // Measure a qubit and collapse the state
        int measure(int target_qubit);

        // Display the state vector
        void display_state() const;
    };
}

#endif // QUANTUM_STATE_HPP

