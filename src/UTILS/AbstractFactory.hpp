//
// Created by ehrustic on 30/03/18.
//

#ifndef ISAE_ML_ABSTRACTFACTORY_H
#define ISAE_ML_ABSTRACTFACTORY_H

#include <iostream>
#include <functional>
#include <unordered_map>
#include <cassert>

namespace ISAE_ML {
    namespace UTILS {
        template<class Key, class Object, class... Args>
        class AbstractFactory {
        public:
            using Creator = std::function<Object(Args...)>;

            void Register(Key const &key, Creator const &creator);

            Object Create(Key const &key, Args &&... args);

        private:
            std::unordered_map <Key, Creator> m_map;
        };

        template<class Key, class Object, class... Args>
        void AbstractFactory<Key, Object, Args...>::Register(const Key &key, const AbstractFactory::Creator &creator) {
            assert(this->m_map.count(key) == 0);
            assert(creator);
            this->m_map.emplace(key, creator);
        }

        template<class Key, class Object, class... Args>
        Object AbstractFactory<Key, Object, Args...>::Create(const Key &key, Args &&... args) {
            assert(this->m_map.count(key) == 1);
            assert(this->m_map[key]);
            return this->m_map[key](std::forward<Args>(args)...);
        }
    }
}

#endif //ISAE_ML_ABSTRACTFACTORY_H
