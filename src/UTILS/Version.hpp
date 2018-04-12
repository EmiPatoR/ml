//
// Created by ehrustic on 11/04/18.
//

#ifndef ISAE_ML_VERSION_HPP
#define ISAE_ML_VERSION_HPP

#include <Config.hpp>
#include <sstream>

namespace ISAE_ML {
    namespace UTILS {
        class Version {
        public:
            static std::string getFullVersion(void){
                std::stringstream ss;
                ss << ISAE_ML_VERSION_MAJOR << "." << ISAE_ML_VERSION_MINOR;
                return ss.str();
            }
        };
    }
}

#endif //ISAE_ML_VERSION_HPP
