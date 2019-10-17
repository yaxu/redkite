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
#include "RkLog.h"

RkListView::RkListViewImpl::RkListViewImpl(RkListView *interface, RkWidget *parent)
    : RkWidgetImpl(static_cast<RkWidget*>(interface), parent)
    , inf_ptr{interface}
    , listViewModel{nullptr}
    , offsetIndex{-1}
    , cellPadding{4}
    , cellHeight{20}
{
}

void RkListView::RkListViewImpl::setModel(RkModel *model)
{
        listViewModel = model;
        RK_ACT_BIND(listViewModel, modelChanged, RK_ACT_ARGS(), this, modelChanged());
        if (listViewModel->rows() > 0)
                offsetIndex = 0;
}

void RkListView::RkListViewImpl::modelChanged()
{
        offsetIndex = -1;
        if (listViewModel->rows() > 0)
                offsetIndex = 0;
        inf_ptr->update();
}

RkModel* RkListView::RkListViewImpl::getModel() const
{
        return listViewModel;
}

void RkListView::RkListViewImpl::draw(RkPainter &painter)
{
        if (!listViewModel || offsetIndex < 0)
                return;

        auto pen = painter.pen();
        auto font = painter.font();
        int offsetY = 0;
        for (auto index = offsetIndex; index < listViewModel->rows(); index++) {
                auto data = listViewModel->data(index, RkModel::DataType::Text);
                if (std::holds_alternative<std::string>(data)) {
                        auto height = drawCellText(index, painter, offsetY, std::get<std::string>(data));
                        offsetY += height;
                }
                painter.setPen(pen);
                painter.setFont(font);
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

        RkRect rect{0, offsetY, inf_ptr->width(), cellHeight};

        data = listViewModel->data(index, RkModel::DataType::Background);
        if (std::holds_alternative<RkColor>(data))
                painter.fillRect(rect, std::get<RkColor>(data));

        rect.setTopLeft({cellPadding, offsetY});
        rect.setWidth(inf_ptr->width()- cellPadding);
        data = listViewModel->data(index, RkModel::DataType::Color);
        if (std::holds_alternative<RkColor>(data)) {
                auto pen = painter.pen();
                pen.setColor(std::get<RkColor>(data));
                painter.setPen(pen);
        }

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

void RkListView::RkListViewImpl::setCellHeight(int height)
{
        cellHeight = height;
}

int RkListView::RkListViewImpl::getCellHeight() const
{
        return cellHeight;
}

void RkListView::RkListViewImpl::incrementOffsetIndex(int val)
{
        if (listViewModel->rows() < 1 || val == 0)
                return;
        else if (offsetIndex + val < 0)
                offsetIndex = 0;
        else if (offsetIndex > listViewModel->rows() - 1)
                offsetIndex = listViewModel->rows() - 1;
        else
                  offsetIndex += val;
        inf_ptr->update();
}

int RkListView::RkListViewImpl::getOffsetIndex() const
{
        return offsetIndex;
}

int RkListView::RkListViewImpl::getCellIndex(const RkPoint &point) const
{
        if ((point.y() > inf_ptr->height() || point.y() < 0))
                return -1;
        return point.y() / cellHeight;
}

size_t RkListView::RkListViewImpl::visibleRows() const
{
        return inf_ptr->height() / cellHeight + (inf_ptr->height() % cellHeight ? 1 : 0);
}
