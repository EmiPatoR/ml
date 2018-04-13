# Finding required Libs
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

if(GPU)
    find_package(CUDA REQUIRED)
    set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}-D_FORCE_INLINES;-gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=[sm_50,compute_50] -gencode arch=compute_52,code=[sm_52,compute_52])
    cuda_add_library(ISAE_ML
            SHARED
            DNN/Activation.cpp DNN/Layer.cpp
            DNN/LinearActivation.cpp
            UTILS/AbstractFactory.hpp
            UTILS/Version.hpp
            UTILS/LinAlg.hpp
            UTILS/LinAlg.cu
            )
    CUDA_ADD_CUBLAS_TO_TARGET( ISAE_ML )
else()
    add_library(ISAE_ML
            SHARED
            DNN/Activation.cpp DNN/Layer.cpp
            DNN/LinearActivation.cpp
            UTILS/AbstractFactory.hpp
            UTILS/Version.hpp
            UTILS/LinAlg.hpp
            )

endif()

# Linking Libraries
target_link_libraries (ISAE_ML Eigen3::Eigen)

install(TARGETS ISAE_ML
        DESTINATION lib)

file(
        GLOB_RECURSE
        dnn_headers
        DNN/*.hpp
)

file(
        GLOB_RECURSE
        utils_headers
        UTILS/*.hpp
)

install(FILES ${dnn_headers}
        DESTINATION include/${CMAKE_PROJECT_NAME}/DNN)

install(FILES ${utils_headers}
        DESTINATION include/${CMAKE_PROJECT_NAME}/UTILS)