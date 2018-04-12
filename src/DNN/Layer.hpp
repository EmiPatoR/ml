//
// Created by ehrustic on 04/04/18.
//

#ifndef ISAE_ML_LAYER_H
#define ISAE_ML_LAYER_H


/*!
 * \file Layer.hpp
 * \brief Implementation of Base abstract class for activation functions
 * \author HRUSTIC Emir
 * \version @@
 */


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
