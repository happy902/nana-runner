// Created by walkinsky(lyh6188@hotmail.com), 2018/11/09
#include "stdafx.h"

#include <nana/runner/sample/editor_cntrl.h>

#include <nana/runner/sample/logger_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/editor_view.h>
#include <nana/runner/sample/editor_setup_view_impl.h>

#include <nana/runner/app_base.h>

using namespace nana::runner::sample;

void editor_cntrl::initialize()
{
    add_view<login_view>();
    add_view<logger_view>();
    add_view<editor_view>();
    add_view<editor_setup_view_impl>();
}

void editor_cntrl::on_init()
{
    login_ = app::show_view<login_view>();
    login_->cast<login_view>().login_.events().click([&] {
        login_->close();
        log_ = app::show_view<logger_view>();
        editor_ = app::show_view<editor_view>();
        editor_->cast<editor_view>().setup_.events().click([&] {
            editor_setup_ = app::show_view<editor_setup_view_impl>();
            editor_setup_->cast<editor_setup_view_impl>().set_target(&editor_->cast<editor_view>().filebuf_);
        });
    });
}

void editor_cntrl::on_fini()
{
    close_view(log_);
    close_view(login_);
    close_view(editor_);
    close_view(editor_setup_);
}
