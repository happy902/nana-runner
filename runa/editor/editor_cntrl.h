// Created by walkinsky(lyh6188@hotmail.com), 2018/02/12
#pragma once

#include <runa/foundation/controller_base.h>

namespace runa::editor {

    class editor_cntrl : public controller_obj
    {
        NAR_DEFINE_OBJECT(editor_cntrl, controller_obj);

		view_ptr logger_;
        view_ptr editor_;
		view_ptr editor_setup_;

    public:
        editor_cntrl();

        void open(callback _on_complete);

        void close();

    };

}
