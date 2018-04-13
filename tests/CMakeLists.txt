find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/src/DNN
        ${CMAKE_SOURCE_DIR}/src/UTILS
        ${Boost_INCLUDE_DIRS}
        )

if(GPU)
    find_package(CUDA REQUIRED)

    CUDA_INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/tests
            ${CMAKE_SOURCE_DIR}/src/DNN
            ${CMAKE_SOURCE_DIR}/src/UTILS
            ${Boost_INCLUDE_DIRS}
            )

    # NVCC flags
    set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}-D_FORCE_INLINES;-gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=[sm_50,compute_50] -gencode arch=compute_52,code=[sm_52,compute_52])
    add_definitions(-DBOOST_TEST_DYN_LINK)

    file(
            GLOB
            unit_tests
            *.cpp
    )

    foreach (t ${unit_tests})
        get_filename_component(testName ${t} NAME_WE)
        cuda_add_executable(${testName} ${t})
        CUDA_ADD_CUBLAS_TO_TARGET( ${testName} )

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

else()

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
endif()