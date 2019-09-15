/**
 * File name: RkModel.h
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

#ifndef RK_MODEL_H
#define RK_MODEL_H

#include "Rk.h"
#include "RkVariant.h"

class RkEventQueue;

class RK_EXPORT RkModel {
 public:
    enum class DataType: int {
            Alignment = 0,
            Font = 1,
            Color = 2,
            Text = 3,
            Background = 4
    };

    RkModel(RkEventQueue *queue)
            : eventQueue{queue}
            , selectedModelIndex{-1}
        {}
    virtual ~RkModel() = default;
    RK_DECL_ACT(updated, updated(), RK_ARG_TYPE(), RK_ARG_VAL());
    virtual RkVariant data(int index, DataType type) const = 0;
    virtual size_t rows() const = 0;
    void selectIndex(int index)
    {
            if (rows() > 0 && index > -1 && index < rows())
                    selectedModelIndex = index;
    }

    int selectedIndex() const
    {
            return selectedModelIndex;
    }

 private:
    RkEventQueue* eventQueue;
    int selectedModelIndex;
};

#endif // RK_MODEL_H
