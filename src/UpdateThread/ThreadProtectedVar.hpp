#pragma once

#include <mutex>

namespace robot_remote_control
{

/**
 * @brief Template class to make variables thread save
 * 
 * @tparam C The class type to have thread save
 */
template <class C> class ThreadProtecetedVar{

    public:

        ThreadProtecetedVar():
            islocked(false)
        {};

        virtual ~ThreadProtecetedVar(){};

        /**
         * @brief get a copy of the contained variable
         * 
         * @return const C a copy of the protected variable
         */
        const C get(){
            std::lock_guard<std::mutex> lock(mutex);
            C returnvar = var;
            return returnvar;
        }

        /**
         * @brief set the protected variable
         * 
         * @param val the new value
         */
        void set(const C &val){
            std::lock_guard<std::mutex> lock(mutex);
            var = val;
        }

        /**
         * @brief lock the protected variable manually to allow a reference access
         */
        void lock(){
            mutex.lock();
            islocked = true;
        }

        /**
         * @brief unlock the protected variable after it was manually locked
         */
        void unlock(){
            islocked = false;
            mutex.unlock();
        }

        /**
         * @brief Get the protected variable as reference allowing direct access
         * 
         * @return C& reference to the protected variable
         */
        C& get_ref(){
            if (!islocked){
                throw std::runtime_error("ThreadProtecetedVar must be locked before get_ref() is used");
            }
            return var;
        }
        
    private:
        C var;
        bool islocked;
        std::mutex mutex;

};

}