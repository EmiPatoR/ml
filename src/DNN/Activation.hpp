//
// Created by ehrustic on 30/03/18.
//

#ifndef ISAE_ML_ACTIVATIONS_H
#define ISAE_ML_ACTIVATIONS_H

/*!
 * \file Activation.hpp
 * \brief Definition of Base abstract class for activation functions
 * \author HRUSTIC Emir
 * \version 0.1
 */

#include <iostream>

namespace ISAE_ML {
    namespace DNN {
        class Activation {

        protected:
            std::string _name;


        public:
            virtual double computeGradient(double x) const = 0;

            virtual double computeActication(double x) const = 0;

            std::string getName(void);
        };
    }
}

#endif //ISAE_ML_ACTIVATIONS_H
