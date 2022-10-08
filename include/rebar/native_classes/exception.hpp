//
// Created by maxng on 10/2/2022.
//

#ifndef REBAR_NATIVE_EXCEPTION_HPP
#define REBAR_NATIVE_EXCEPTION_HPP

#include "../native_template.hpp"
#include "../environment.hpp"
#include "load.hpp"

namespace rebar::native {
    struct exception : public native_template<> {
        REBAR_NATIVE_CLASS(exception, "EXCEPTION");

        REBAR_NATIVE_FUNCTION(GetObject) {
            REBAR_RETURN(env->get_exception_object());
        }

        REBAR_NATIVE_FUNCTION(GetType) {
            REBAR_RETURN(env->get_exception_type());
        }

        REBAR_NATIVE_FUNCTION(GetStackTrace) {
            REBAR_RETURN(env->str(env->generate_exception_message()));
        }

        REBAR_NATIVE_FUNCTION(PrintStackTrace) {
            std::cout << env->generate_exception_message() << std::endl;
            REBAR_RETURN(null);
        }
    };

    object load_exception(environment& a_env) {
        exception e(a_env);
        return e.build_object();
    }
}

#endif //REBAR_NATIVE_EXCEPTION_HPP
