#include <LinAlg.hpp>
#include <Eigen/Dense>

int main(int argc, char *argv[]) {

    Eigen::MatrixXf A = Eigen::MatrixXf::Constant(10, 10, 1.0);
    Eigen::MatrixXf B = Eigen::MatrixXf::Constant(10, 10, 3.0);

    Eigen::MatrixXf C = ISAE_ML::UTILS::LinAlg::matrixMult(A, B);

    std::cout << " C = " << C;

    return 0;
}