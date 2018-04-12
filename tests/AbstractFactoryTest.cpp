//
// Created by ehrustic on 05/04/18.
//
#define BOOST_TEST_MODULE AbstractFactoryTest

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "TestObj.hpp"

#define private public // for testing purpose
#include <UTILS/AbstractFactory.hpp>


struct Fixture{
    Fixture(){
        BOOST_TEST_MESSAGE("Setup Fixture");
        testFactory.Register("TestObj", [](int arg1, float arg2, std::string arg3) {return std::unique_ptr<TestObj>(new TestObj(arg1, arg2, arg3));});
    }

    ~Fixture(){
        BOOST_TEST_MESSAGE("Teardown Fixture");
    }

    using TestFactory = ISAE_ML::UTILS::AbstractFactory<std::string, std::unique_ptr<TestObj>, int, float, std::string>;
    TestFactory testFactory;
};

BOOST_FIXTURE_TEST_SUITE(s, Fixture)

//_________________________________________________________________________________________ //

    BOOST_FIXTURE_TEST_CASE(FactoryRegisterTest, Fixture){
        BOOST_CHECK( testFactory.m_map.count("TestObj") == 1);
    }

//_________________________________________________________________________________________ //

    BOOST_FIXTURE_TEST_CASE(FactoryCreateTest, Fixture) {
        std::unique_ptr<TestObj> obj = testFactory.Create("TestObj", 1, 2.5, "Hello");
        BOOST_CHECK(obj->getArg1() == 1);
        BOOST_CHECK(obj->getArg2() == 2.5);
        BOOST_CHECK(obj->getArg3() == "Hello");
    }
//_________________________________________________________________________________________ //
BOOST_AUTO_TEST_SUITE_END()