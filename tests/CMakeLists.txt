find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        )

add_definitions(-DBOOST_TEST_DYN_LINK)

file(
        GLOB
        unit_tests
        *.cpp
)

foreach (t ${unit_tests})
    get_filename_component(testName ${t} NAME_WE)
    add_executable(${testName} ${t})

    target_link_libraries(${testName} ISAE_ML
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            )

    if(${testName} MATCHES 'Eigen*')
        target_link_libraries(${testName} Eigen3::Eigen)
    elseif(${testName} MATCHES 'LinAlg*')
        target_link_libraries(${testName} Eigen3::Eigen)
    endif()

endforeach (t)