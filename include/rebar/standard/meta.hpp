//
// Created by maxng on 6/25/2022.
//

#ifndef REBAR_META_HPP
#define REBAR_META_HPP

#include "macro.hpp"

#include "../rebar.hpp"

namespace rebar::library::standard {
    struct meta : public library {
        meta() : library(usage::explicit_include) {}

        static REBAR_FUNCTION(GetFunctionInfo) {
            auto func_object = env->arg(0);

            if (func_object.is_function()) {
                function func = func_object.get_function(*env);

                function_info& info = env->get_function_info(func);

                table* info_table = new table;

                (*info_table)[env->str("Name")] = env->str(info.get_name());
                (*info_table)[env->str("Origin")] = env->str(info.get_origin());
                (*info_table)[env->str("ID")] = static_cast<integer>(info.get_id());

                *ret = info_table;
                return;
            }

            *ret = null;
        }

        static REBAR_FUNCTION(Test) {
            std::cout << env->arg(0) << std::endl;

            *ret = null;
        }

        object load(environment& a_environment) override {
            table* lib_table = new table;

            (*lib_table)[a_environment.str("GetFunctionInfo")] = a_environment.bind(GetFunctionInfo, "GetFunctionInfo", "REBAR::STD::META");
            (*lib_table)[a_environment.str("Test")] = a_environment.bind(Test, "Test", "REBAR::STD::META");

            return lib_table;
        }
    };

    const char library_meta[] = "Meta";
    define_library<library_meta, meta> d_meta;
}

#endif //REBAR_META_HPP
