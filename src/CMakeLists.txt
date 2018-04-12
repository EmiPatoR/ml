# Finding required Libs
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

if(GPU)
    find_package(CUDA)
    cuda_add_library(ISAE_ML
            SHARED
            DNN/Activation.cpp DNN/Layer.cpp
            DNN/LinearActivation.cpp
            UTILS/AbstractFactory.hpp
            UTILS/Version.hpp
            UTILS/LinAlg.hpp
            )
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