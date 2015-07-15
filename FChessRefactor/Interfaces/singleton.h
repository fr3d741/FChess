#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

template <class T>
class Singleton
{
    static std::shared_ptr<T> _instance;
public:

    template <typename... Args>
    static std::shared_ptr<T> Instance(Args... args)
    {
        if (!_instance)
        {
            _instance = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
        }

    return _instance;
    }

};

template<class T> std::shared_ptr<T> Singleton<T>::_instance;

#endif // SINGLETON_H
