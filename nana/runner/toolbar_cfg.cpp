// Created by walkinsky(lyh6188@hotmail.com), 2018/10/20
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include "toolbar_cfg.h"

#include <nana/runner/view_base.h>
#include <nana/runner/app_base.h>

void nana::runner::toolbar_cfg::init_widget(widget & _w, view_obj* _root_view) const
{
    super::init_widget(_w, _root_view);

    auto& w = dynamic_cast<ui_type&>(_w);
    if (!scale_().empty())
        w.scale(scale_().value());

    for (size_t i=0; i<children_().size(); ++i)
    {
        auto& child = children_()[i]->cast<option_cfg>();
        if (child.empty())
            w.separate();
        else if (child.image_().empty())
            w.append(child.get_caption());
        else
            w.append(child.get_caption(), app::create_image(child.image_()));

        if (!child.enabled_().empty())
            w.enable(i, child.enabled_().value());

        if (!child._click_().empty())
        {
            string cmd = child._click_();
            if (cmd == "close")
                w.events().selected([i, _root_view](nana::arg_toolbar const& _a) { if (_a.button == i) _root_view->close(); });
            else if (cmd == "quit")
                w.events().selected([i](nana::arg_toolbar const& _a) { if (_a.button==i) app::quit(); });
            else
                w.events().selected([i, cmd](nana::arg_toolbar const& _a) { if (_a.button == i) app::create_view(cmd); });
        }
    }
}

#endif

