//
// Created by ehrustic on 11/04/18.
//

#ifndef ISAE_ML_LINALG_HPP
#define ISAE_ML_LINALG_HPP

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include <stdexcept>
#include <sstream>
#ifdef GPU
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <cublas_v2.h>
#endif

namespace ISAE_ML{
    namespace UTILS{
        class LinAlg{
        public:

            static Eigen::MatrixXf matrixMult(const Eigen::MatrixXf& A, const Eigen::MatrixXf& B){

                // Check Matrix dimensions
                if(A.cols() != B.rows()){
                    std::stringstream ss;
                    ss << "Your matrices dimensions disagrees : A=(" << A.rows() << ", " << A.cols() << ") and B = (" <<
                       B.rows() << ", " << B.cols() << ")" ;
                    throw std::length_error(ss.str().c_str());
                }

#ifndef GPU
                std::cout << "CPU COMP" << std::endl;
                return A*B;
#else
                std::cout << "GPU COMP" << std::endl;

                // Allocating and copying Matrices on GPU
                thrust::device_vector<float> d_A(A.data(), A.data() + A.rows() * A.cols());
                thrust::device_vector<float> d_B(B.data(), B.data() + B.rows() * B.cols());
                thrust::device_vector<float> d_C((unsigned long)A.rows() * B.cols());

                //Allocating result matrix on CPU
                thrust::host_vector<float> h_C ((unsigned long)A.rows() * B.cols());

                // Pointers to the Matrices
                float* pd_A = thrust::raw_pointer_cast(&d_A[0]);
                float* pd_B = thrust::raw_pointer_cast(&d_B[0]);
                float* pd_C = thrust::raw_pointer_cast(&d_C[0]);
                float* ph_C = thrust::raw_pointer_cast(&h_C[0]);

                // cuBLAS params
                const float alf = 1;
                const float bet = 0;
                const float *alpha = &alf;
                const float *beta = &bet;

                int m = (int) A.rows();
                int n = (int) A.cols();
                int k = (int) B.cols();

                int lda = m;
                int ldb = k;
                int ldc = m;

                // Init handle
                cublasHandle_t handle;
                cublasCreate_v2(&handle);

                // Do the multiplication
                cublasSgemm_v2(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, pd_A, lda,
                               pd_B, ldb, beta, pd_C, ldc);

                // Destroy Handle
                cublasDestroy_v2(handle);

                thrust::copy(d_C.begin(), d_C.end(), h_C.begin());

                //std::cout << "test = " << h_C << std::endl;

                //return Eigen::MatrixXf::Constant(10,10, 1.0);
                return Eigen::Map<Eigen::MatrixXf>(ph_C, A.rows(), B.cols());

#endif

            }

        };
    }
}


#endif //ISAE_ML_LINALG_HPP
