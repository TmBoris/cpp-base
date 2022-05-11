#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    std::size_t n = table.size();
    for (std::size_t x = 0; x < n; x++) {
        for (std::size_t y = 0; y < n; y++) {
            for (std::size_t z = 0; z < n; z++) {
                if (table[table[x][y]][z] != table[x][table[y][z]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
