#include <iostream>
#include <vector>

// 1. The Base "Label" (CRTP)
template <typename Derived>
struct Expression {
    double operator()(int i) const { 
        return static_cast<const Derived&>(*this)(i); 
    }
};

// 2. Physical Data Storage
struct Vector : Expression<Vector> {
    std::vector<double> data;
    Vector(std::initializer_list<double> list) : data(list) {}
    
    // Physical access to data
    double operator()(int i) const { return data[i]; }
};

// 3. The "Lazy" Addition Object
template <typename LHS, typename RHS>
struct VecAdd : Expression<VecAdd<LHS, RHS>> {
    const LHS& l;
    const RHS& r;
    VecAdd(const LHS& lhs, const RHS& rhs) : l(lhs), r(rhs) {}

    // Math only happens HERE, when the user asks for a specific index
    double operator()(int i) const { return l(i) + r(i); }
};

// 4. Overload + to return the Lazy Object instead of a Vector
template <typename LHS, typename RHS>
VecAdd<LHS, RHS> operator+(const Expression<LHS>& a, const Expression<RHS>& b) {
    return VecAdd<LHS, RHS>(static_cast<const LHS&>(a), static_cast<const RHS&>(b));
}

int main() {
    Vector A = {1.0, 2.0, 3.0};
    Vector B = {4.0, 5.0, 6.0};

    auto sum = A + B; // This does ZERO math. 'sum' is just a VecAdd object.

    std::cout << "The math happens now: " << sum(1) << std::endl; // Output: 7.0
}