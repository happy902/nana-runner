// Created by walkinsky(lyh6188@hotmail.com), 2018/10/12
#include "stdafx.h"

#include "picture_cfg.h"

#include <nana/runner/app_base.h>

void nana::runner::picture_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<ui_type&>(_w);

    if (!align_().empty() || !align_v_().empty())
    {
        nana::align h = !align_().empty() ? align_().value().value() : nana::align::left;
        nana::align_v v = !align_v_().empty() ? align_v_().value().value() : nana::align_v::top;
        w.align(h, v);
    }

    if (!gradual_from_().empty() || !gradual_to_().empty() || !gradual_horizontal_().empty())
    {
        w.set_gradual_background(get_color(gradual_from_()), get_color(gradual_to_()), gradual_horizontal_().value());
    }

    if (!stretchable_().empty())
        w.stretchable(stretchable_().value());

    if (!transparent_().empty())
        w.transparent(transparent_().value());

    if (!file_().empty())
    {
        wstring fullpath;
        if (app::instance().search_file(to_wstring(file_()), fullpath))
        {
            w.load(nana::paint::image{ fullpath });
        }
    }
}