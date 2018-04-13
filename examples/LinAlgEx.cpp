#include <LinAlg.hpp>
#include <Eigen/Dense>

int main(int argc, char *argv[]) {

    Eigen::MatrixXf A = Eigen::MatrixXf::Constant(3, 4, 1.0);
    Eigen::MatrixXf B = Eigen::MatrixXf::Constant(4, 5, 1.0);

    Eigen::MatrixXf C = ISAE_ML::UTILS::LinAlg::matrixMult(A, B);

    Eigen::MatrixXf D = ISAE_ML::UTILS::LinAlg::transpose(C);

    std::cout << " C = " << C << std::endl << "Ct = " << D << std::endl;

    return 0;
}