#include "linalg.hpp"


namespace cpputil {
namespace linalg {


/** Return if two rank-4 tensors are approximately equal
 */
bool areEqual(const Eigen::Tensor<double, 4>& M, const Eigen::Tensor<double, 4>& T, const double tolerance){
    auto dim = M.dimension(0);

    // Since Eigen::Tensor doesn't have an isApprox yet, we will check every pair of values manually
    for (int i = 0; i < dim ; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                for (int l = 0; l < dim; l++) {
                    if (std::abs(M(i,j,k,l) - T(i,j,k,l)) > tolerance) {
                        return false;
                    }
                }
            }
        }
    } // rank-4 tensor traversing
    return true;
}


}  // namespace linalg
}  // namespace cpputil

