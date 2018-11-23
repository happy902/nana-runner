// Created by walkinsky(lyh6188@hotmail.com), 2017/11/15
#include "stdafx.h"

#ifndef __NANA_RUNNER_LIB_ALL_IN_ONE

#include <nana/runner/istr.h>

runa::istr& runa::istr::advance(int _offset)
{
    if (_offset > (int)size_)
        _offset = (int)size_;
    data_ += _offset;
    size_ -= _offset;
    return *this;
}

runa::istr runa::istr::substr(size_t _start, size_t _len) const
{
    if (_start > size_)
        _start = size_;
    if (_len > size_ - _start)
        _len = size_ - _start;
    return istr{ data_ + _start, _len };
}

runa::istr runa::istr::read(std::function<bool(char)> _fn, size_t _maxLen)
{
    istr& p = me();
    istr beg = p;
    while (p && _fn(*p) && _maxLen--)
        ++p;
    return istr{ beg, p };
}

runa::istr runa::istr::read_until(std::function<bool(char)> _fn, size_t _maxLen)
{
    istr& _p = me();
    istr beg = _p;
    while (_p && !_fn(*_p) && _maxLen--)
        ++_p;
    return istr{ beg, _p };
}

int runa::istr::compare(istr _v) const
{
    size_t n = size();
    if (n > _v.size())
        n = _v.size();
    for (size_t i = 0; i < n; ++i)
    {
        if (me()[i] < _v[i])
            return -1;
        if (me()[i] > _v[i])
            return 1;
    }
    if (size() < _v.size())
        return -1;
    if (size() > _v.size())
        return 1;
    return 0;
}

#endif

