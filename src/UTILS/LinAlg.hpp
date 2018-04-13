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
#define BLOCK_DIM 16
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <cublas_v2.h>
#endif

namespace ISAE_ML{
    namespace UTILS{
        class LinAlg{
        public:
#ifndef GPU

            static Eigen::MatrixXf matrixMult(const Eigen::MatrixXf& A, const Eigen::MatrixXf& B, bool transposeA=false,
                bool transposeB=false){
                Eigen::MatrixXf AToUse = A, BToUse = B;
                if(transposeA)
                    AToUse = A.transpose();
                if(transposeB)
                    BToUse = B.transpose();
                if(AToUse.cols() != BToUse.rows()){
                    std::stringstream ss;
                    ss << "Your matrices dimensions disagrees : A=(" << A.rows() << ", " << A.cols() << ") and B = (" <<
                       B.rows() << ", " << B.cols() << ")" ;
                    throw std::length_error(ss.str().c_str());
                }
                return AToUse*BToUse;
            }


            static Eigen::MatrixXf transpose(const Eigen::MatrixXf& A){
                return A.transpose();
            }
#else
            static Eigen::MatrixXf matrixMult(const Eigen::MatrixXf& A, const Eigen::MatrixXf& B, bool transposeA=false,
                                              bool transposeB=false);
            static Eigen::MatrixXf transpose(const Eigen::MatrixXf& A);
#endif
        };
    }
}


#endif //ISAE_ML_LINALG_HPP
