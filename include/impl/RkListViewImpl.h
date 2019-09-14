/**
 * File name: RkListViewImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
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

#ifndef RK_LISTVIEW_IMPL_H
#define RK_LISTVIEW_IMPL_H

#include "RkWidgetImpl.h"
#include "RkPainter.h"

class RkModel;

class RkLineEdit::RkListViewImpl : public RkWidget::RkWidgetImpl {
 public:
        RkListViewImpl(RkLineEdit *interface,  RkWidget *parent = nullptr);
        virtual ~RkListViewImpl();
        void draw(RkPainter &painter);
        void setModel(RkModel *model);
        RkModel* getModel() const;
        void setCellPadding(int padding);
        int getCellPadding() const;

 protected:
        int drawCellText(size_t index,
                         RkPainter &painter,
                         int offsetY,
                         const std::string &text);

 private:
    RK_DECALRE_INTERFACE_PTR(RkListView)
    RkModel *listViewModel;
    size_t offsetIndex;
    int cellPadding;
};

#endif // RK_LISTVIEW_IMPL_H
