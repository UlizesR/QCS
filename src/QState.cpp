#include "QState.hpp"
#include "QBitManipulation.hpp"
#include <cmath>
#include <iostream>

namespace QCS
{
    QState::QState(uint8_t num_qubits_) : num_qubits(num_qubits_)
    {
        // Calculate the size as Eigen::Index
        Eigen::Index size = static_cast<Eigen::Index>(1ULL << num_qubits);
        state = CVector::Constant(size, Complex(0.0, 0.0));
        state(0) = 1.0; // Initialize to |0...0>
    }

    void QState::apply_gate(const CMatrix& gate, const std::vector<int>& target_qubits)
    {
        int k = target_qubits.size();

        // Validate gate dimensions
        if(gate.rows() != gate.cols())
            throw std::invalid_argument("Gate must be a square matrix.");
        if(gate.rows() != (1 << k))
            throw std::invalid_argument("Gate size does not match number of target qubits.");

        // Validate target qubits
        for(auto q : target_qubits)
        {
            if(q < 0 || q >= num_qubits)
                throw std::out_of_range("Target qubit index out of range.");
        }

        size_t N = state.size();
        std::vector<int> sorted_qubits = target_qubits;
        std::sort(sorted_qubits.begin(), sorted_qubits.end());

        uint64_t mask = create_bitmask(sorted_qubits);
        int num_targets = sorted_qubits.size();
        size_t step = 1ULL << num_targets;
        size_t num_iterations = N / step;

        // Handle single-qubit gates with optimized routine
        if(num_targets == 1 && gate.rows() == 2)
        {
            apply_single_qubit_gate(gate, sorted_qubits[0]);
            return;
        }

        // General multi-qubit gate application
        for(size_t i = 0; i < num_iterations; ++i)
        {
            size_t base = i * step;
            Eigen::VectorXcd substate = state.segment(base, step);
            Eigen::VectorXcd new_substate = gate * substate;
            state.segment(base, step) = new_substate;
        }
    }

    void QState::apply_single_qubit_gate(const CMatrix& gate, int qubit)
    {
        uint64_t step = 1ULL << qubit;
        uint64_t N = state.size();

        for(uint64_t i = 0; i < N; i += (step << 1))
        {
            for(uint64_t j = 0; j < step; ++j)
            {
                uint64_t idx0 = i + j;
                uint64_t idx1 = idx0 + step;

                if(idx1 >= N) continue;

                Complex a = state(idx0);
                Complex b = state(idx1);

                state(idx0) = gate(0,0)*a + gate(0,1)*b;
                state(idx1) = gate(1,0)*a + gate(1,1)*b;
            }
        }
    }

    int QState::measure(int target_qubit)
    {
        if(target_qubit < 0 || target_qubit >= num_qubits)
            throw std::out_of_range("Target qubit index out of range.");

        double prob_zero = 0.0;
        double prob_one = 0.0;

        size_t N = state.size();
        uint64_t mask = 1ULL << target_qubit;

        for(size_t i = 0; i < N; ++i)
        {
            if((i & mask) == 0)
                prob_zero += std::norm(state(i));
            else
                prob_one += std::norm(state(i));
        }

        // Normalize probabilities
        double total_prob = prob_zero + prob_one;
        if(total_prob == 0.0)
            throw std::runtime_error("Total probability is zero. Invalid state vector.");

        prob_zero /= total_prob;
        prob_one /= total_prob;

        // Generate random number
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double rand_num = dis(gen);

        int result = (rand_num < prob_zero) ? 0 : 1;

        // Collapse the state vector
        for(size_t i = 0; i < N; ++i)
        {
            if( ((i & mask) >> target_qubit) != result )
                state(i) = Complex(0.0, 0.0);
        }

        // Normalize the state vector
        double norm = std::sqrt(state.squaredNorm());
        if(norm > 0.0)
            state /= norm;
        else
            throw std::runtime_error("State vector norm is zero after measurement.");

        std::cout << "Measurement outcome on qubit " << target_qubit << ": " << result << std::endl;
        return result;
    }

    void QState::display_state() const
    {
        std::cout << "Quantum State Vector:" << std::endl;
        for(int i = 0; i < state.size(); ++i)
        {
            // Convert index to binary string
            std::string basis = "";
            for(int q = num_qubits - 1; q >= 0; --q)
            {
                basis += ((i & (1 << q)) ? "1" : "0");
            }
            std::cout << "|" << basis << "> : " << state(i) << std::endl;
        }
    }
}

