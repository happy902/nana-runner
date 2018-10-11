// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#pragma once

#include <nana/runner/widget_cfg.h>

#include <nana/gui/widgets/label.hpp>

namespace nana::runner {

    using label = nana::label;

    class label_cfg : public widget_cfg
    {
        NAR_DEFINE_WIDGET(label, widget_cfg);

        NAR_FIELD(optional<bool>, transparent);
        NAR_FIELD(optional<align>, align);
        NAR_FIELD(optional<align_v>, align_v);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            super::traverse(_s);
            NAR_CODEC(_s, transparent);
            NAR_CODEC(_s, align);
            NAR_CODEC(_s, align_v);
        }

        static wnd_ptr create_wnd_(window p, bool v) { return std::make_shared<ui_type>(p, v); }

        void init_widget(widget& _w) const override;

    };

}
