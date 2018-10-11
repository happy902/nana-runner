// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <nana/runner/base.h>

#include <nana/runner/app_base.h>

#include <nana/runner/sample/editor_ctr.h>

namespace nana::runner::sample {

    class editor_app : public app
    {
		editor_ctr editor_;

    public:
		void on_init() override
		{
			editor_ctr::initialize();

			editor_.on_init();
		}

        void on_fini() override
        {
            editor_.on_fini();
        }

    };

}

