#include "LinAlg.hpp"

//Print matrix A(nr_rows_A, nr_cols_A) storage in column-major format
 void print_matrix(const float *A, int nr_rows_A, int nr_cols_A) {

    for (int i = 0; i < nr_rows_A; ++i) {
        for (int j = 0; j < nr_cols_A; ++j) {
            std::cout << A[j * nr_rows_A + i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Eigen::MatrixXf ISAE_ML::UTILS::LinAlg::transpose(const Eigen::MatrixXf &A) {
    // Allocation and copy to GPU Memory
    thrust::device_vector<float> d_A(A.data(), A.data() + A.rows() * A.cols());
    thrust::device_vector<float> d_B((unsigned long) A.cols() * A.rows());
    thrust::device_vector<float> d_At((unsigned long) A.cols() * A.rows());

    // Allocation to CPU Memory
    thrust::device_vector<float> h_At((unsigned long) A.cols() * A.rows());

    // Pointers
    float* pd_A = thrust::raw_pointer_cast(&d_A[0]);
    float* pd_B = thrust::raw_pointer_cast(&d_B[0]);
    float* pd_At = thrust::raw_pointer_cast(&d_At[0]);
    float* ph_At = thrust::raw_pointer_cast(&h_At[0]);

    // Init handle
    cublasHandle_t handle;
    cublasCreate_v2(&handle);

    const float alf = 1;
    const float bet = 0;
    const float* alpha = &alf;
    const float* beta = &bet;

    int m = (int) A.rows();
    int n = (int) A.cols();

    //TODO CORRECT NOT WORKING
    // Do the transposition
    cublasSgeam(handle, CUBLAS_OP_T,CUBLAS_OP_T,n,m,alpha,pd_A,n,beta,pd_B,n,pd_At,n);

    std::cout << "TEST" << std::endl;
    // Copy from device to host
    thrust::copy(d_At.begin(), d_At.end(), h_At.begin());
    print_matrix(ph_At,A.rows(), A.cols());

    // Destroy Handle
    cublasDestroy_v2(handle);

    return Eigen::Map<Eigen::MatrixXf>(ph_At, A.cols(), A.rows());
}

Eigen::MatrixXf ISAE_ML::UTILS::LinAlg::matrixMult(const Eigen::MatrixXf& A, const Eigen::MatrixXf& B, bool transposeA,
                           bool transposeB){


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
    int n = (int) B.cols();
    int k = (int) A.cols();

    int lda = m;
    int ldb = k;
    int ldc = m;

    // Init handle
    cublasHandle_t handle;
    cublasCreate_v2(&handle);

    // Do we need to Transpose ?
    cublasOperation_t trA = (transposeA ? CUBLAS_OP_T : CUBLAS_OP_N);
    cublasOperation_t trB = (transposeB ? CUBLAS_OP_T : CUBLAS_OP_N);

    // Do the multiplication

    cublasSgemm_v2(handle, trA, trB, m, n, k, alpha, pd_A, lda,
                   pd_B, ldb, beta, pd_C, ldc);


    // Copy from device to host
    thrust::copy(d_C.begin(), d_C.end(), h_C.begin());


    // Destroy Handle
    cublasDestroy_v2(handle);


    // Return result
    return Eigen::Map<Eigen::MatrixXf>(ph_C, A.rows(), B.cols());
}


