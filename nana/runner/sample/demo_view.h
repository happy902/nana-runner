// Created by walkinsky(lyh6188@hotmail.com), 2017/11/10
#pragma once

#include <nana/runner/view_base.h>

#include <nana/runner/widget_all.h>

#include <nana/runner/app_base.h>

namespace nana::runner::sample::view {

    class Demo : public view_obj
    {
        form& form_;

        menubar& menubar_;

        categorize& categorize_;

        label& label_;
        combox& align_;
        combox& align_v_;
        align m_label_align{ nana::align::left };
        align_v m_label_align_v{ nana::align_v::top };
        //color
        textbox& bg_;
        textbox& fg_;
        //font
        textbox& name_;
        textbox& size_;
        checkbox& bold_;
        checkbox& italic_;
        checkbox& strikeout_;
        checkbox& underline_;

        textbox& text_;
        checkbox& editable_;
        checkbox& linewrap_;
        checkbox& multilines_;
        slider& tsize_;
        slider& clevel_;
        group& talign_;
        align m_text_align{ nana::align::left };
        group& tcolor_;
        widget_cfg* tcolor_cfg_{};

        combox& picsel_;
        widget_cfg* picsel_cfg_{};
        size_t picidx_{ 0 };
        picture& picture_;

        date_chooser& date_;
        hscroll& hscr_;
        vscroll& vscr_;
        listbox& listbox_;

        tabbar& tabs_1_bar_;
        tabbar_lite& tabs_2_bar_;
        //treebox& folder_;
        //listbox& files_;

        //float_listbox

        progress& prog_;
        spinbox& spin_;

        button& quit_;

    public:
        static pcstr type_name_() { return "demo"; }
        static view_ptr new_(widget_cfg& _cfg, window _parent) { return std::make_shared<Demo>(_cfg, _parent); }

    public:
        Demo(widget_cfg& _cfg, window _parent)
            : view_obj{ _cfg, _parent }
            , form_{ wnd<form>() }
            , menubar_{ wnd<menubar>("menubar") }
            , categorize_{ wnd<categorize>("categorize") }
            , label_{ wnd<label>("label.value") }
            , align_{ wnd<combox>("label.align") }
            , align_v_{ wnd<combox>("label.align_v") }
            , bg_{ wnd<textbox>("color.bg.value") }
            , fg_{ wnd<textbox>("color.fg.value") }
            , name_{ wnd<textbox>("f.name.value") }
            , size_{ wnd<textbox>("f.size.value") }
            , bold_{ wnd<checkbox>("font.bold") }
            , italic_{ wnd<checkbox>("font.italic") }
            , strikeout_{ wnd<checkbox>("font.strikeout") }
            , underline_{ wnd<checkbox>("font.underline") }
            , text_{ wnd<textbox>("text") }
            , editable_{ wnd<checkbox>("txtcmd.editable") }
            , linewrap_{ wnd<checkbox>("txtcmd.linewrap") }
            , multilines_{ wnd<checkbox>("txtcmd.multilines") }
            , tsize_{ wnd<slider>("p1.tsize") }
            , clevel_{ wnd<slider>("p1.clevel") }
            , picsel_{ wnd<combox>("p1.picsel") }
            , picsel_cfg_{ cfg_("p1.picsel") }
            , talign_{ wnd<group>("p2.align") }
            , tcolor_{ wnd<group>("p2.color") }
            , tcolor_cfg_{ cfg_("p2.color") }
            , picture_{ wnd<picture>("p2.picture") }
            , date_{ wnd<date_chooser>("p3.date.value") }
            , hscr_{ wnd<hscroll>("p3.date.hscr") }
            , vscr_{ wnd<vscroll>("p3.vscr.value") }
            , listbox_{ wnd<listbox>("p3.table") }
            , tabs_1_bar_{ wnd<tabbar>("tabs.1.bar") }
            , tabs_2_bar_{ wnd<tabbar_lite>("tabs.2.bar") }
            //, folder_{ wnd<treebox>("tabs.1.bar.folder.tree") }
            //, files_{ wnd<listbox>("tabs.2.bar.files.list") }
            , prog_{ wnd<progress>("cmd.prog") }
            , spin_{ wnd<spinbox>("cmd.spin") }
            , quit_{ wnd<button>("cmd.close") }
        {
            set_log_handler([this](const string& s) {
                write_console(s);
                text_.append(s, false);
            });

            categorize_.caption(fs::current_path());

            label_.text_align(m_label_align.value(), m_label_align_v.value());
            align_ << m_label_align;
            align_v_ << m_label_align_v;
            align_.events().selected([this] {
                align_ >> m_label_align;
                label_.text_align(m_label_align.value(), m_label_align_v.value());
            });
            align_v_.events().selected([this] {
                align_v_ >> m_label_align_v;
                label_.text_align(m_label_align.value(), m_label_align_v.value());
            });

            bg_ << label_.bgcolor();
            fg_ << label_.fgcolor();
            bg_.events().focus([this] {
                label_.bgcolor(get_color(bg_.caption()));
            });
            fg_.events().focus([this] {
                label_.fgcolor(get_color(fg_.caption()));
            });

            auto tf = label_.typeface();
            name_ << tf.name();
            size_ << tf.size();
            bold_ << tf.bold();
            italic_ << tf.italic();
            strikeout_ << tf.strikeout();
            underline_ << tf.underline();
            name_.events().text_changed([this] {
                font f = label_.typeface();
                label_.typeface(make_font(name_.caption(), f.size(), f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            size_.events().text_changed([this] {
                font f = label_.typeface();
                double sz = 0;
                size_ >> sz;
                label_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });
            bold_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), bold_.checked(), f.italic(), f.underline(), f.strikeout()));
            });
            italic_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), italic_.checked(), f.underline(), f.strikeout()));
            });
            strikeout_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), f.underline(), strikeout_.checked()));
            });
            underline_.events().checked([this] {
                font f = label_.typeface();
                label_.typeface(make_font(f.name(), f.size(), f.bold(), f.italic(), underline_.checked(), f.strikeout()));
            });

            editable_.events().checked([this] {
                text_.editable(editable_.checked());
            });
            linewrap_.events().checked([this] {
                text_.line_wrapped(linewrap_.checked());
            });
            multilines_.events().checked([this] {
                text_.multi_lines(multilines_.checked());
            });

            tsize_.value((unsigned)text_.typeface().size());
            tsize_.events().value_changed([this] {
                font f = text_.typeface();
                double sz = tsize_.value();
                text_.typeface(make_font(f.name(), sz, f.bold(), f.italic(), f.underline(), f.strikeout()));
            });

            init_group(talign_, m_text_align, [this] {
                talign_ >> m_text_align;
                text_.text_align(m_text_align.value());
            });

            clevel_.events().value_changed([this] {update_text_color(); });
            for (auto& i : tcolor_cfg_->cast<group_cfg>().radios()) {
                i->events().click([this] {update_text_color(); });
            }

            picsel_.events().selected([this] {
                picidx_ = picsel_.option();
                string fname = picsel_cfg_->children_()[picidx_]->cast<option_cfg>().image_();
                picture_.load(app::create_image(fname));
                spin_.value(std::to_string((unsigned)(prog_.amount()*(1+picidx_)/picsel_cfg_->children_().size())));
            });
            picture_.events().click([this] {
                ++picidx_;
                if (picidx_ >= picsel_cfg_->children_().size())
                    picidx_ = 0;
                picsel_.option(picidx_);
            });

            date_.events().date_changed([this]{
                NAR_LOG("selected date = " << date_.read());
            });

            hscr_.events().value_changed([this] {
                NAR_LOG("hscroll value = " << hscr_.value());
            });
            vscr_.events().value_changed([this] {
                NAR_LOG("vscroll value = " << vscr_.value());
            });

            spin_.events().text_changed([this] {
                prog_.value((unsigned)spin_.to_int());
            });

            //quit_.events().click([this] { close(); });
        }

        void update_text_color()
        {
            unsigned r = tcolor_.option_checked(0) ? clevel_.value() : 0;
            unsigned g = tcolor_.option_checked(1) ? clevel_.value() : 0;
            unsigned b = tcolor_.option_checked(2) ? clevel_.value() : 0;
            text_.bgcolor({ r, g, b });
            text_.fgcolor({ ~r, ~g, ~b });
        }

    };

}

