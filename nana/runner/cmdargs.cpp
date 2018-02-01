// Created by walkinsky(lyh6188@hotmail.com), 2018/01/31
#include "stdafx.h"

#include <nana/runner/cmdargs.h>

void nana::runner::cmdargs::init(const wchar_t* _cmdline)
{
    cmdline_ = _cmdline;
    string_split(cmdline_, args_);

    for (size_t i = 0; i < args_.size(); ++i)
    {
        auto const & s = args_[i];
        if (s[0] == '-')
        {
            wstring name(s);
            name.erase(0, 1);
            
            wstring value;
            if (i + 1 < args_.size())
                value = args_[++i];

            options_.add(name, value);
        }
        else
        {
            arguments_.push_back(s);
        }
    }
}