// nana_runner.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <nana/runner/sample/editor_app.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    nana::runner::sample::editor_app a;
    a.run(lpCmdLine);
    return 0;
}
  