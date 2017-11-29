/*!
 * @file smart_ptr.h
 * @brief contains smart pointer make utilities
 */
#ifndef EREBOS_SMART_PTR_H
#define EREBOS_SMART_PTR_H

#include <memory>

namespace erebos {

    namespace smart_ptr {
        /*!
	     * @tparam UniqueType : the type for unique_ptr
	     * @tparam TypeArgs : type for passed parameter to the pointer which unique_ptr will hold
	     * @param args_fwd : parameter to be passed to the pointer which unique_ptr will hold
	     * @return new std::unique_ptr<UniqueType> instance
	     * @brief simple implementation if you're not using C++14 or later
	     */
        template<typename UniqueType, typename ... TypeArgs>
        inline std::unique_ptr<UniqueType> make_unique(TypeArgs &&... args_fwd) {
            return std::unique_ptr<UniqueType>(new UniqueType(std::forward<TypeArgs>(args_fwd)...));
        }

        /*!
         * @tparam SharedType : the type for shared_ptr
         * @tparam TypeArgs : type for passed parameter to the pointer which shared_ptr will hold
         * @param args_fwd : parameter to be passed to the pointer which shared_ptr will hold
         * @return new std::unique_ptr<SharedType> instance
         * @brief simple implementation if you're not using C++14 or later
         */
        template<typename SharedType, typename ... TypeArgs>
        inline std::shared_ptr<SharedType> make_shared(TypeArgs &&... args_fwd) {
            return std::shared_ptr<SharedType>(new SharedType(std::forward<TypeArgs>(args_fwd)...));
        }

        /*!
         * @tparam WeakType : the type for weak_ptr
         * @tparam TypeArgs : type for passed parameter to the pointer which weak_ptr will hold
         * @param args_fwd : parameter to be passed to the pointer which weak_ptr will hold
         * @return new std::weak_ptr<WeakType> instance
         * @brief simple implementation if you're not using C++14 or later
         */
        template<typename WeakType, typename ... TypeArgs>
        inline std::weak_ptr<WeakType> make_weak(TypeArgs &&... args_fwd) {
            return std::weak_ptr<WeakType>(new WeakType(std::forward<TypeArgs>(args_fwd)...));
        }
    }
}

#endif //EREBOS_SMART_PTR_H
