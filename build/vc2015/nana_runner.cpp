// nana_runner.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "nana_runner.h"

#include <nana/runner/hello_view.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    using namespace nana::runner;
    app<view::Hello> app(lpCmdLine);
}
