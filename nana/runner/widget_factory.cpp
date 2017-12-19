// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#include "stdafx.h"

#include <nana/runner/widget_factory.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/button_cfg.h>

nana::runner::widget_factory::widget_factory()
{
    add("form",    new_<form_cfg>()());
    add("label",   new_<label_cfg>()());
    add("textbox", new_<textbox_cfg>()());
    add("button",  new_<button_cfg>()());
}

nana::runner::widget_factory & nana::runner::widget_factory::instance()
{
    static widget_factory __;
    return __;
}

nana::runner::widget_cfg* nana::runner::widget_factory::create(const string& _type)
{
    auto f = instance().get(_type);
    if (f)
        return f();
    return nullptr;
}

void nana::runner::widget_factory::add(const string & _type, create_func _func)
{
    widgets_[_type] = _func;
}

nana::runner::create_func nana::runner::widget_factory::get(const string & _type) const
{
    auto i = widgets_.find(_type);
    if (i == widgets_.end())
        return nullptr;
    return (*i).second;
}