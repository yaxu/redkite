/**
 * File name: RkLabelImpl.cpp
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

#include "RkLabelImpl.h"

RkLabelImpl::RkLabelImpl(RkLabel *interface, const std::string &text = std::string())
    : RkWidgetImpl(static_cast<RkWidget*>interface, interface->parent())
    , inf_ptr{interface}
    , labelText{text}
{
}

RkLabelImpl::~RkLabelImpl()
{
}

void RkLabelImpl::setText(std:string &text);
{
        labelText = text;
}

std::string RkLabelImpl::text() const
{
        return labelText;
}