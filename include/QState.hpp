#ifndef Q_STATE_HPP
#define Q_STATE_HPP

#include "QTypes.hpp"

namespace QCS
{
class QState
{
public:
    uint8_t num_qubits;
    CVector state;

    QState(uint8_t num_qubits);

    void set_state(const CVector &new_state);

    void apply_gate(const CMatrix &gate, const CVector &target_qubits);

    void measure(const uint8_t target_qubit);

    void display_state() const;
};
}

#endif // Q_STATE_HPP
