//
// Created by ehrustic on 11/04/18.
//

#define BOOST_TEST_MODULE LinAlgTest

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <Eigen/Dense>
#include <LinAlg.hpp>


struct Fixture{

    // Some test cases
    Eigen::MatrixXf m = Eigen::MatrixXf::Constant(3,3,1.0); // Creates a ones 3x3 double matrix
    Eigen::MatrixXf n = Eigen::MatrixXf::Constant(3,4,1.0);
    Eigen::MatrixXf o = Eigen::MatrixXf::Constant(4,5,1.0);
    Eigen::VectorXf v = Eigen::VectorXf::Constant(3,1.0); // Creates a ones 3x1 vector

    Fixture(){
        BOOST_TEST_MESSAGE("Setup Fixture");
    }

    ~Fixture(){
        BOOST_TEST_MESSAGE("Teardown Fixture");
    }


};

BOOST_FIXTURE_TEST_SUITE(s, Fixture)

//_________________________________________________________________________________________ //

    BOOST_FIXTURE_TEST_CASE(EigenVectorMatMultTest, Fixture){
        //Test Matrix-Vector multiplication
        BOOST_CHECK( m*v == Eigen::VectorXf::Constant(3,3.0));
    }

    BOOST_FIXTURE_TEST_CASE(MatMultTest, Fixture){
        //Test Matrix-Matrix multiplication
        BOOST_CHECK(ISAE_ML::UTILS::LinAlg::matrixMult(n, o) == Eigen::MatrixXf::Constant(3,5,4.0));
    }

    BOOST_FIXTURE_TEST_CASE(TransposeTest, Fixture){
        //Test Matrix-Matrix transposition
//        BOOST_CHECK(ISAE_ML::UTILS::LinAlg::transpose(Eigen::MatrixXf::Constant(3,5,4.0)) ==
//                            Eigen::MatrixXf::Constant(5,3,4.0));
    }

BOOST_AUTO_TEST_SUITE_END()