// Created by walkinsky(lyh6188@hotmail.com), 2018/10/02
#pragma once

#include <nana/runner/base.h>

namespace runa {

	using point = nana::point;
	using size = nana::size;
	using font = nana::paint::font;
	using color = nana::color;
	using colors = enum_<nana::colors, nana::colors::black>;
	using cursor = enum_<nana::cursor, nana::cursor::arrow>;
	using align = enum_<nana::align, nana::align::left>;
	using align_v = enum_<nana::align_v, nana::align_v::top>;
    using event_code = enum_<nana::event_code, nana::event_code::end>;
    using mouse = enum_<nana::mouse, nana::mouse::any_button>;
    using wheel = enum_<nana::arg_wheel::wheel, nana::arg_wheel::wheel::vertical>;

    using widget = nana::widget;
	using wnd_ptr = ptr<widget>;

    color get_color(const string& _s, color _default = {});

	font make_font(const string& _name, double _size, bool _bold, bool _italic, bool _underline, bool _strikeout);

	dumper& operator<<(dumper& _d, const point& _v);
	void operator >> (const parser& _p, point& _v);

	dumper& operator<<(dumper& _d, const size& _v);
	void operator >> (const parser& _p, size& _v);

	dumper& operator<<(dumper& _d, const font& _v);
	void operator >> (const parser& _p, font& _v);

    void operator<<(string& _w, const color& _v);
	void operator >> (const string& _w, color& _v);

    dumper& operator<<(dumper& _d, const color& _v);

    dumper& operator<<(dumper& _d, const nana::arg_click& _v);
    dumper& operator<<(dumper& _d, const nana::arg_mouse& _v);
    dumper& operator<<(dumper& _d, const nana::arg_wheel& _v);

    inline nana::color make_rgb_255(double _r, double _g, double _b)
    {
        return nana::color{ static_cast<uint>(_r), static_cast<uint>(_g), static_cast<uint>(_b) };
    }

    inline nana::color make_rgb(double _r, double _g, double _b)
    {
        return make_rgb_255(_r * 255, _g * 255, _b * 255);
    }

    inline bool pt_in_rect(const nana::point& _p, const nana::rectangle& _r)
    {
        return _p.x >= _r.x && _p.y >= _r.y && _p.x <= _r.right() && _p.y <= _r.bottom();
    }

}

namespace nana {

    inline std::ostream& operator<<(std::ostream& _os, const widget& _v)
    {
        return _os << _v.caption();
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::color& _v)
    {
        return _os << runa::dump(_v);
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::arg_mouse& _v)
    {
        return _os << runa::dump(_v);
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::arg_click& _v)
    {
        return _os << runa::dump(_v);
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::arg_wheel& _v)
    {
        return _os << runa::dump(_v);
    }

}