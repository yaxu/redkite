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

#include "RkListView.h"
#include "RkWidgetImpl.h"
#include "RkPainter.h"
#include "RkVariant.h"

class RkModel;

class RkListView::RkListViewImpl : public RkWidget::RkWidgetImpl {
 public:
        RkListViewImpl(RkListView *interface,  RkWidget *parent = nullptr);
        virtual ~RkListViewImpl() = default;
        RK_DISABLE_COPY(RkListViewImpl)
        RK_DISABLE_MOVE(RkListViewImpl)
        void setModel(RkModel *model);
        void modelChanged();
        RkModel* getModel() const;
        void draw(RkPainter &painter);
        void setCellPadding(int padding);
        int getCellPadding() const;
        void setCellHeight(int height);
        int getCellHeight() const;
        void incrementOffsetIndex(int val);
        int getOffsetIndex() const;
        int getCellIndex(const RkPoint &point) const;
        bool indexVisible(int index) const;
        size_t visibleRows() const;

 protected:
        int drawCellText(size_t index,
                         RkPainter &painter,
                         int offsetY,
                         const std::string &text);

 private:
    RK_DECALRE_INTERFACE_PTR(RkListView)

    RkModel *listViewModel;
    int offsetIndex;
    int cellPadding;
    int cellHeight;
};

#endif // RK_LISTVIEW_IMPL_H
