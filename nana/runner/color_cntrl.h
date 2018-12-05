// Created by walkinsky(lyh6188@hotmail.com), 2018/12/04
#pragma once

#include <nana/runner/controller_base.h>

#include <nana/runner/color_view_impl.h>

#include <nana/runner/color_model.h>

namespace runa {

    class color_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(color_cntrl, controller_obj);

        view_ptr view_;

        using model_type = color_model;
        model_proxy<model_type> model_;

    public:
        color_cntrl();
        ~color_cntrl();

        void open(const model_type& _input, model_type::on_result _on_result);

        void close();

    };

}

