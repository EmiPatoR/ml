//
// Created by ehrustic on 04/04/18.
//

#ifndef ISAE_ML_LAYER_H
#define ISAE_ML_LAYER_H


#include <functional>

namespace ISAE_ML {
    namespace DNN {
        class Layer {
            virtual void forward() const = 0;

            virtual void backward() const = 0;

            virtual void update() const = 0;
        };
    }
}

#endif //ISAE_ML_LAYER_H
