#ifndef Q_BIT_MANIPULATION_HPP
#define Q_BIT_MANIPULATION_HPP

#include <vector>
#include <cstdint>
#include <algorithm>
#include <bitset>

namespace QCS
{
    // Function to create a bitmask for given positions (1-based indexing)
    inline uint64_t create_bitmask(const std::vector<int>& positions)
    {
        uint64_t mask = 0;
        for(auto pos : positions)
        {
            mask |= (1ULL << (pos - 1));
        }
        return mask;
    }

    // Function to check if the target bits match the mask
    inline bool is_match(uint64_t index, uint64_t mask, uint64_t target)
    {
        return (index & mask) == target;
    }

    // Function to compute leading zeros
    inline int leading_zeros(uint64_t x)
    {
        if(x == 0) return 64;
        return __builtin_clzll(x);
    }

    // Function to compute log2 integer
    inline int log2i(uint64_t x)
    {
        if(x == 0) throw std::invalid_argument("log2i undefined for x=0");
        return 63 - leading_zeros(x);
    }

    // Function to compute bmask similar to Julia's bmask
    inline uint64_t bmask(int first, int last)
    {
        return ((1ULL << (last - first + 1)) - 1) << (first - 1);
    }

    // Function to compute lmove similar to Julia's lmove
    inline uint64_t lmove(uint64_t b, uint64_t mask, int k)
    {
        return ((b & ~mask) << k) | (b & mask);
    }

    // Function to group shifts similar to Julia's group_shift
    void group_shift(const std::vector<int>& locations, std::vector<uint64_t>& masks, std::vector<int>& shift_len)
    {
        int k_prv = -1;
        for(auto k : locations)
        {
            if(k == k_prv + 1)
            {
                shift_len.back() += 1;
            }
            else
            {
                masks.push_back(bmask(1, k)); // Assuming group from bit 1 to k
                shift_len.push_back(1);
            }
            k_prv = k;
        }
    }
}

#endif // Q_BIT_MANIPULATION_HPP
