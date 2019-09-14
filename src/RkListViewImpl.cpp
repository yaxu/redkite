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
#include "RkModel.h"

RkListView::RkListViewImpl::RkListViewImpl(RkListView *interface, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , listViewModel{nullptr}
    , offsetIndex{0}
    , cellPadding{4}
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
        if (!listViewModel)
                return;

        int offsetY = 0;
        for (auto index = offsetIndex; index < listViewModel->rows(); index++) {
                auto data = listViewModel->data(index, RkModel::DataType::Text);
                if (std::holds_alternative<std::string>(data)) {
                        auto height = drawCellText(index, painter, offsetY, std::get<std::string>(data));
                        offsetY += height;
                }
                if (offsetY > inf_ptr->height())
                        break;
        }
}

int RkListView::RkListViewImpl::drawCellText(size_t index,
                                             RkPainter &painter,
                                             int offsetY,
                                             const std::string &text)
{
        auto data = listViewModel->data(index, RkModel::DataType::Alignment);
        auto alignment = Rk::Alignment::AlignLeft;
        if (std::holds_alternative<Rk::Alignment>(data))
                alignment = std::get<Rk::Alignment>(data);

        data = listViewModel->data(index, RkModel::DataType::Font);
        if (std::holds_alternative<RkFont>(data))
                painter.setFont(std::get<RkFont>(data));

        data = listViewModel->data(index, RkModel::DataType::Color);
        if (std::holds_alternative<RkColor>(data)) {
                auto pen = painter.pen();
                pen.setColor(std::get<RkColor>(data));
                painter.setPen(pen);
        }

        RkRect rect{cellPadding,
                    offsetY,
                    inf_ptr->width() - cellPadding,
                    painter.font().size() + 2 * cellPadding};
        painter.drawText(rect, text, alignment);
        return rect.height();
}

void RkListView::RkListViewImpl::setCellPadding(int padding)
{
        cellPadding = padding;
}

int RkListView::RkListViewImpl::getCellPadding() const
{
        return cellPadding;
}
