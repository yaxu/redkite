/**
 * File name: RkListView.h
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

#ifndef RK_LISTVIEW_H
#define RK_LISTVIEW_H

#include "RkWidget.h"

class RkModel;

class RK_EXPORT RkListView : public RkWidget {
 public:
    RkListView(RkWidget *parent);
    virtual ~RkListView() = default;
    RK_DISABLE_COPY(RkListView)
    RK_DISABLE_MOVE(RkListView)
    void setModel(RkModel *model);
    RkModel* model() const;
    void setCellPadding(int padding);
    int cellPadding() const;
    RK_DECL_ACT(selectedIndex,
                selectedIndex(int index),
                RK_ARG_TYPE(int),
                RK_ARG_TYPE(index));

 protected:
    RK_DELCATE_IMPL_PTR(RkListView)

    void paintEvent(const std::shared_ptr<RkPaintEvent> &event) final;
    void mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event) final;
    void mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event) final;
    void mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event) final;
    void wheelEvent(const std::shared_ptr<RkWheelEvent> &event) final;
    void mouseDoubleClickEvent(const std::shared_ptr<RkMouseEvent> &event) final;
    void keyPressEvent(const std::shared_ptr<RkKeyEvent> &event) final;
};

#endif // RK_LISTVIEW_H
