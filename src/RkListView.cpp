/**
 * File name: RkListView.cpp
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

#include "RkListView.h"
#include "RkListViewImpl.h"
#include "RkEvent.h"
#include "RkLog.h"

RkListView::RkListView(RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkWidget::RkWidgetImpl>(std::make_shared<RkListView::RkListViewImpl>(this, parent)))
        , impl_ptr{std::static_pointer_cast<RkListView::RkListViewImpl>(o_ptr)}
{
        show();
}

void RkListView::setModel(RkModel *model)
{
        impl_ptr->setModel(model);
        update();
}

RkModel* RkListView::model() const
{
        return impl_ptr->getModel();
}

void RkListView::setCellPadding(int padding)
{
        impl_ptr->setCellPadding(padding);
}

int RkListView::cellPadding() const
{
        return impl_ptr->getCellPadding();
}

void RkListView::paintEvent(const std::shared_ptr<RkPaintEvent> &event)
{
        RkPainter painter(this);
        painter.fillRect(rect(), background());
        auto pen = painter.pen();
        pen.setColor(textColor());
        painter.setPen(pen);
        impl_ptr->draw(painter);
}

void RkListView::mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event)
{
}

void RkListView::mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event)
{

}

void RkListView::mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event)
{
}

void RkListView::mouseDoubleClickEvent(const std::shared_ptr<RkMouseEvent> &event)
{
}

void RkListView::wheelEvent(const std::shared_ptr<RkWheelEvent> &event)
{
        if (event->direction() == RkWheelEvent::Direction::WheelUp
            || event->direction() == RkWheelEvent::Direction::WheelDown)
                impl_ptr->incrementOffsetIndex(event->direction() == RkWheelEvent::Direction::WheelDown ? 1 : -1);
}
