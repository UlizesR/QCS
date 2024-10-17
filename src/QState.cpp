#include "QState.hpp"

QState::QState(uint8_t num_qubits)
{
    this->num_qubits = num_qubits;
    this->state = CVector::Zero(1 << num_qubits);
    this->state(0) = Complex(1, 0);
}

void QState::set_state(const CVector &new_state)
{
    this->state = new_state;
}

void QState::apply_gate(const CMatrix &gate, const CVector &target_qubits)
{

}

void QState::measure(const uint8_t target_qubit)
{

}

void QState::display_state() const
{
    std::cout << this->state << std::endl;
}
