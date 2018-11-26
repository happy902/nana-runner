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

    using widget = nana::widget;
	using wnd_ptr = ptr<widget>;

	color get_color(const string& _s);

	font make_font(const string& _name, double _size, bool _bold, bool _italic, bool _underline, bool _strikeout);

	dumper& operator<<(dumper& _d, const point& _v);
	void operator >> (const parser& _p, point& _v);

	dumper& operator<<(dumper& _d, const size& _v);
	void operator >> (const parser& _p, size& _v);

	dumper& operator<<(dumper& _d, const font& _v);
	void operator >> (const parser& _p, font& _v);

	void operator<<(string& _w, const color& _v);
	void operator >> (const string& _w, color& _v);

    dumper& operator<<(dumper& _d, const nana::arg_click& _v);
    dumper& operator<<(dumper& _d, const nana::arg_mouse& _v);

}

namespace nana {

    inline std::ostream& operator<<(std::ostream& _os, const widget& _v)
    {
        return _os << _v.caption();
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::arg_mouse& _v)
    {
        return _os << runa::dump(_v);
    }

    inline std::ostream& operator<<(std::ostream& _os, const nana::arg_click& _v)
    {
        return _os << runa::dump(_v);
    }

}