//
// Created by ehrustic on 11/04/18.
//

#define BOOST_TEST_MODULE EigenTest

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#define private public // for testing purpose
#include <Eigen/Dense>


struct Fixture{

    Eigen::MatrixXd m; // Creates a ones 3x3 double matrix
    Eigen::VectorXd v; // Creates a ones 3x1 vector

    Fixture(){
        BOOST_TEST_MESSAGE("Setup Fixture");
        m = Eigen::MatrixXd::Constant(3,3,1.0);
        v = Eigen::VectorXd::Constant(3,1.0);
    }

    ~Fixture(){
        BOOST_TEST_MESSAGE("Teardown Fixture");
    }


};

BOOST_FIXTURE_TEST_SUITE(s, Fixture)

//_________________________________________________________________________________________ //

    BOOST_FIXTURE_TEST_CASE(EigenVectorMatMultTest, Fixture){
        //Test Matrix-Vector multiplication
        BOOST_CHECK( m*v == Eigen::VectorXd::Constant(3,3.0));
    }

BOOST_AUTO_TEST_SUITE_END()