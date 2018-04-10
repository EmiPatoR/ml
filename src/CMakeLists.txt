add_library(ISAE_ML
        SHARED
        DNN/Activation.cpp DNN/Layer.cpp UTILS/AbstractFactory.hpp DNN/LinearActivation.cpp)

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