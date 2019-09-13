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

RkListView(RkWidget *parent)
        : RkWidget(parent, std::static_pointer_cast<RkWidget::RkWidgetImpl>(std::make_shared<RkListView::RkListViewImpl>(this, parent))))
        , impl_ptr{std::static_pointer_cast<RkListView::RkListViewImpl>(o_ptr)}
{
}

void RkListView::setModel(RkModel *model)
{
        impl_ptr->setMode(model);
        update();
}

RkModel* RkListView::model() const
{
        return impl_ptr->getModel();
}

void RkListView::paintEvent(const std::shared_ptr<RkPaintEvent> &event)
{
        RkPainter painter(this);
        impl_ptr->draw(painter);
}

void RkListView::mouseMoveEvent(const std::shared_ptr<RkMouseEvent> &event) final
{
}

void RkListView::mouseButtonPressEvent(const std::shared_ptr<RkMouseEvent> &event) final
{
}

void RkListView::mouseButtonReleaseEvent(const std::shared_ptr<RkMouseEvent> &event) final
{
}

void RkListView::mouseDoubleClickEvent(const std::shared_ptr<RkMouseEvent> &event) final
{
}

void RkListView::wheelEvent(const std::shared_ptr<RkWheelEvent> &event) final
{
}
