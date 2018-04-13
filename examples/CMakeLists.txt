include_directories(${CMAKE_SOURCE_DIR}/src/DNN
        ${CMAKE_SOURCE_DIR}/src/UTILS)

if(GPU)
    find_package(CUDA REQUIRED)
    CUDA_INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/DNN
            ${CMAKE_SOURCE_DIR}/src/UTILS)
    # nvcc flags
    set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}-D_FORCE_INLINES;-gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=[sm_50,compute_50] -gencode arch=compute_52,code=[sm_52,compute_52])


    file(
            GLOB
            usage_examples
            *.cpp
    )

    foreach (f ${usage_examples})
        get_filename_component(exampleName ${f} NAME_WE)
        cuda_add_executable(${exampleName} ${f})
        target_link_libraries(${exampleName} ISAE_ML)

        if(${exampleName} MATCHES 'Eigen*')
            target_link_libraries(${exampleName} Eigen3::Eigen)
        elseif(${exampleName} MATCHES 'LinAlg*')
            target_link_libraries(${exampleName} Eigen3::Eigen)
        endif()

        install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${exampleName}
                DESTINATION bin
                RENAME ${CMAKE_PROJECT_NAME}-${exampleName})
    endforeach (f)

else()

    file(
            GLOB
            usage_examples
            *.cpp
    )

    foreach (f ${usage_examples})
        get_filename_component(exampleName ${f} NAME_WE)
        add_executable(${exampleName} ${f})
        target_link_libraries(${exampleName} ISAE_ML)

        if(${exampleName} MATCHES 'Eigen*')
            target_link_libraries(${exampleName} Eigen3::Eigen)
        elseif(${exampleName} MATCHES 'LinAlg*')
            target_link_libraries(${exampleName} Eigen3::Eigen)
        endif()

        install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${exampleName}
                DESTINATION bin
                RENAME ${CMAKE_PROJECT_NAME}-${exampleName})
    endforeach (f)

endif()