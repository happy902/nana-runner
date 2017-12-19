// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/view_base.h>

namespace nana::runner {

    class widget_cfg;
    using view_ptr = std::shared_ptr<widget_cfg>;
    using wnd_ptr = std::shared_ptr<widget>;

    class widget_cfg
    {
        NAR_FIELD(id, id);
        NAR_FIELD(string, caption);
        NAR_FIELD(string, div);
        NAR_FIELD(optional<bool>, line_wrapped);
        NAR_FIELD(string, bgcolor);
        NAR_FIELD(string, fgcolor);
        NAR_FIELD(std::vector<view_ptr>, children);

        widget_cfg* m_parent{ nullptr };

        // only for root(form)
        using _Widgets = std::map<id, wnd_ptr>;
        NAR_FIELD(_Widgets, widgets);

    public:
        template<class _Stream>
        void traverse(_Stream& _s)
        {
            NAR_CODEC(_s, id);
            NAR_CODEC(_s, caption);
            NAR_CODEC(_s, div);
            NAR_CODEC(_s, line_wrapped);
            NAR_CODEC(_s, bgcolor);
            NAR_CODEC(_s, fgcolor);
            NAR_CODEC(_s, children);
        }

        virtual ~widget_cfg() = default;

        virtual string type_name() const = 0;

        virtual widget* create_widget(window p, bool v) const = 0;

        virtual void init_widget(widget& _w) const;

        template<class T>
        T& cast()
        {
            return dynamic_cast<T&>(*this);
        }

        template<class T>
        const T& cast() const
        {
            return dynamic_cast<const T&>(*this);
        }

        id id_name() const
        {
            if (!m_parent || id_().empty())
                return id_();
            return m_parent->id_name() / id_();
        }

        void set_parent(widget_cfg* _parent)
        {
            m_parent = _parent;
        }

        void from_file(wstring const& _filename);

        widget* create_wnd(nana::window _parent_wnd, bool _visible = true) const;

        widget* get_widget_(id _id) const;

        template<class T>
        T& wnd(id _id) const
        {
            widget* w = get_widget_(_id);
            if (!w)
                throw std::invalid_argument("no widget for " + _id.str());
            return dynamic_cast<T&>(*w);
        }

        void make_widgets(nana::window _parent_wnd);
        void make_widgets(widget_cfg& _root, widget_cfg* _parent_cfg, nana::window _parent_wnd);

        string make_div() const
        {
            string s;
            make_div(s);
            return s;
        }
        void make_div(string& _div) const;

        string get_caption() const;

    };
    inline std::ostream& operator<<(std::ostream& _os, const widget_cfg& _v)
    {
        return _os << dump(_v, false, 0, true);
    }
    template<> struct dumpable<widget_cfg> { static constexpr bool value = true; };

}