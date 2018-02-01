// nana_runner.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <nana/runner/app_base.h>

#include <nana/runner/view_factory.h>

#include <nana/runner/sample/log_viewer_view.h>
#include <nana/runner/sample/login_view.h>
#include <nana/runner/sample/hello_view.h>
#include <nana/runner/sample/demo_view.h>
#include <nana/runner/sample/font_view.h>
#include <nana/runner/sample/color_view.h>

namespace nana::runner::sample {

    using namespace view;

    class app : public app_base
    {
        LogViewer* log_{};
        Login* login_{};
        Demo* demo_{};

    public:
        void init_views() override
        {
            add_view<LogViewer>();
            add_view<Login>();
            add_view<Hello>();
            add_view<Demo>();
            add_view<Font>();
            add_view<Color>();
        }

        void init_logic() override
        {
            log_ = get_view<LogViewer>();
            login_ = get_view<Login>();
            demo_ = get_view<Demo>();

            log_->show();
            login_->show();
            login_->on_login([this] {
                demo_->show();
            });
        }

    };

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::sample::app a;
    a.run(lpCmdLine);
    return 0;
}
