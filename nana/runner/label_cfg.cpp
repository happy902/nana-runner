// Created by walkinsky(lyh6188@hotmail.com), 2018/01/12
#include "stdafx.h"

#include "label_cfg.h"

void nana::runner::label_cfg::init_widget(widget & _w) const
{
    super::init_widget(_w);

    auto& w = dynamic_cast<label&>(_w);

    if (!transparent_().empty())
        w.transparent(transparent_().value());
}