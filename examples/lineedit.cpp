/**
 * File name: painter.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"
#include "RkLineEdit.h"

class  LineEditExample: public RkWidget {
  public:
        LineEditExample(RkMain *app)
                : RkWidget(app)
        {
                setSize(350, 350);
                auto lineEdit = new RkLineEdit(this);
                auto font = lineEdit->font();
                font.setSize(30);
                lineEdit->setFont(font);
                lineEdit->setSize(300, 50);
                lineEdit->setPosition((width() - lineEdit->width()) / 2, (height() - lineEdit->height()) / 2);
                lineEdit->setTitle("RkLineEdit");
                lineEdit->setBorderWidth(1);
                lineEdit->setBorderColor(80, 80, 80);
                RK_ACT_BIND(lineEdit, textEdited, RK_ACT_ARGS(const std::string &text), this, onUpdateText(text));
                lineEdit->show();
        }

  protected:
        void keyPressEvent(const std::shared_ptr<RkKeyEvent> &event)
        {
                RK_LOG_INFO("called");
        }
        void mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event)
        {
                //                RK_LOG_INFO("called");
        }
        void onUpdateText(const std::string &text)
        {
                RK_LOG_INFO("text:" << text);
        }
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new LineEditExample(&app);
    widget->setTitle("Line Edit Example");
    widget->show();

    return app.exec();
}
