// Created by walkinsky(lyh6188@hotmail.com), 2017/01/15
#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <functional>

#include <cassert>

#include <nana/gui.hpp>

#define NAR_V(x) m_##x
#define NAR_F(x) x##_

#define NAR_FIELD(t, x) \
        public: \
            t const & NAR_F(x)() const { return NAR_V(x); } \
            t & NAR_F(x)() { return NAR_V(x); } \
            void NAR_F(x)(t const & _v) { NAR_V(x) = _v; } \
        private: \
            t NAR_V(x)

#define NAR_CODEC(s, x) s(#x, NAR_V(x))
#define NAR_CODEC_UNNAMED(s, x) s.unnamed(NAR_V(x))

namespace std {

    template<class T>
    inline std::string& operator<<(std::string& _s, const T& _v)
    {
        std::ostringstream oss;
        oss << _v;
        return _s << oss.str();
    }
    inline std::string& operator<<(std::string& _s, const std::string& _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, char _v)
    {
        return _s += _v;
    }
    inline std::string& operator<<(std::string& _s, const char* _v)
    {
        return _s += _v;
    }
    std::string& operator<<(std::string& _s, const std::wstring& _v);
    std::string& operator<<(std::string& _s, const wchar_t* _v);

    template<class T>
    inline void operator >>(const std::string& _s, T& _v)
    {
        std::istringstream iss{ _s };
        iss >> _v;
    }
    inline void operator >>(const std::string& _s, std::string& _v)
    {
        _v = _s;
    }
    void operator >>(const std::string& _s, std::wstring& _v);

    ostream& operator<<(ostream& _os, const wstring& _v);

}

namespace nana::runner {

    namespace tag
    {
        const char type = '@';
        const char string = '\'';
        const char string2 = '"';
        const char begin = '{';
        const char end = '}';
        const char assign = '=';
        const char space = ' ';
        const char escape = '\\';
        const char comment = '*';

        const std::string newline{ "\n" };
        const std::string indent{ "    " };
    }

    using int8 = char;
    using int16 = short;
    using int32 = int;
    using int64 = __int64;

    using byte = unsigned char;

    using string = std::string;
    using wstring = std::wstring;

    using pcstr = const char*;
    using pcwstr = const wchar_t*;

    using strings = std::vector<string>;

	template<class T> using ptr = std::shared_ptr<T>;

    template<class T> struct dumpable { static constexpr bool value = false; };

    template<class T> using is_simple_type = std::is_arithmetic<T>;

	/*
	 * character functions
	 */

    inline bool is_space(const char c) { return c == ' ' || c == '\t'; }
    inline bool is_newline(const char c) { return c == '\r' || c == '\n'; }
    inline bool is_blank(const char c) { return is_space(c) || is_newline(c); }

    inline bool between(const char c, const char beg, const char end) { return c >= beg && c <= end; }

    inline bool is_digit(const char c) { return between(c, '0', '9'); }
    inline bool is_upper(const char c) { return between(c, 'A', 'Z'); }
    inline bool is_lower(const char c) { return between(c, 'a', 'z'); }
    inline bool is_letter(const char c) { return is_upper(c) || is_lower(c); }
    inline bool is_identifier_start(const char c) { return is_letter(c) || c == '_'; }
    inline bool is_identifier_body(const char c) { return is_identifier_start(c) || is_digit(c); }

    inline bool is_hex_upper(const char c) { return between(c, 'A', 'F'); }
    inline bool is_hex_lower(const char c) { return between(c, 'a', 'f'); }
    inline bool is_hex_letter(const char c) { return is_hex_upper(c) || is_hex_lower(c); }
    inline bool is_hex16_char(const char c) { return is_hex_letter(c) || is_digit(c); }

    inline bool is_base64_char(const char c) { return is_letter(c) || is_digit(c) || c=='+' || c=='/' || c=='='; }

    inline bool is_quote_char(const char c) { return c == '\'' || c == '"'; }

    inline char to_upper(const char c) { return is_lower(c) ? (c - 'a' + 'A') : c; }
    inline char to_lower(const char c) { return is_upper(c) ? (c - 'A' + 'a') : c; }

	/*
	 * utility functions
	 */

    template<class T>
    inline bool is_empty(const T& _v) { return false; }
    inline bool is_empty(const string& _v) { return _v.empty(); }
    inline bool is_empty(const wstring& _v) { return _v.empty(); }
    template<class T>
    inline bool is_empty(const std::vector<T>& _v) { return _v.empty(); }

	/*
	 * string functions
	 */

	string to_string(const wstring& _wstr);
    wstring to_wstring(const string& _utf8str);

    void string_split(const string& _s, std::vector<string>& _ss);
    void string_split(const wstring& _s, std::vector<wstring>& _ss);

	/*
	 * file functions
	 */

	bool read_file(const wstring& _filename, string& _content);
	bool write_file(const wstring& _filename, const string& _content);

	/*
	 * codec template function
	 */

	template<class _Stream, class T>
    inline _Stream& codec(_Stream& _s, T& _v)
    {
        _s.enter(_v.type_name());
        _v.traverse(_s);
        _s.leave();
        return _s;
    }

	/*
	 * root object
	 */

	class object;
    using obj_ptr = ptr<object>;

    class object
    {
    public:
        virtual ~object() = default;

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

	};

}
