// Created by walkinsky(lyh6188@hotmail.com), 2018/02/11
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/form_cfg.h>
#include <nana/runner/textbox_cfg.h>
#include <nana/runner/slider_cfg.h>
#include <nana/runner/checkbox_cfg.h>
#include <nana/runner/label_cfg.h>
#include <nana/runner/button_cfg.h>

namespace nana::runner::sample::view {

    class editor_setup : public view_obj
    {
    public:
        static pcstr type_name_() { return "editor_setup"; }
        static view_ptr new_(widget_cfg& _cfg) { return std::make_shared<editor_setup>(_cfg); }

    public:
        form& form_;

        textbox& name_;
        textbox& size_;
        slider& slider_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& strikeout_;
        checkbox& underline_;

        textbox& sample_;

        button& apply_;
        button& ok_;
        button& cancel_;

    public:
        editor_setup(widget_cfg& _cfg)
            : view_obj{ _cfg }
            , form_{ wnd<form>() }
            , name_{ wnd<textbox>("name.value") }
            , size_{ wnd<textbox>("size.value") }
            , slider_{ wnd<slider>("size.slider") }
            , bold_{ wnd<checkbox>("bold.value") }
            , italic_{ wnd<checkbox>("italic.value") }
            , strikeout_{ wnd<checkbox>("strikeout.value") }
            , underline_{ wnd<checkbox>("underline.value") }
            , sample_{ wnd<textbox>("sample.value") }
            , apply_{ wnd<button>("cmd.apply") }
            , ok_{ wnd<button>("cmd.ok") }
            , cancel_{ wnd<button>("cmd.cancel") }
        {
            name_ << sample_.typeface().name();
            size_ << sample_.typeface().size();

            name_.events().text_changed([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            size_.events().text_changed([this] {
                font f = sample_.typeface();
                double sz = 0;
                size_ >> sz;
                sample_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            slider_.events().value_changed([this] {
                size_ << slider_.value();
            });
            bold_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.underline(), f.strikeout()));
            });
            italic_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.underline(), f.strikeout()));
            });
            strikeout_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.underline(), strikeout_.checked()));
            });
            underline_.events().checked([this] {
                font f = sample_.typeface();
                sample_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), underline_.checked(), f.strikeout()));
            });

            cancel_.events().click([this] {
                close();
            });
        }

    };

}