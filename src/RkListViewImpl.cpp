/**
 * File name: RkListViewImpl.cpp
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

#include "RkListViewImpl.h"
#include "RkPainter.h"
#include "RkLog.h"
#include "RkTimer.h"
#include "RkEvent.h"

RkListView::RkListViewImpl::RkListViewImpl(RkListView *interface, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , listViewModel{nullptr}
{
}

void RkListView::RkListViewImpl::setModel(RkModel *model)
{
        listViewModel = model;
}

RkModel* RkListView::RkListViewImpl::getModel() const
{
        return listViewModel;
}

void RkListView::RkListViewImpl::draw(RkPainter &painter)
{
        for (auto index = offsetIndex; index < listViewModel->rows(); index++) {
                const auto data = listViewModel->data(index);
                switch (data.type()) {
                case RkModel::DataType::Text:
                        drawText(data);
                        break;
                case RkModel::DataType::Image:
                        drawText(data);
                        break;
                }
        }
}

