/**
 * File name: RkVariant.h
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

#ifndef RK_VARIANT_H
#define RK_VARIANT_H

#include "Rk.h"
#include "RkFont.h"
#include "RkColor.h"
#include "RkPoint.h"
#include "RkRealPoint.h"
#include "RkRect.h"
#include "RkSize.h"
#include "RkPen.h"
#include "RkImage.h"

#include <variant>
#include <string>

using RkVariant = std::variant<std::string,
                               unsigned int,
                               float,
                               double,
                               bool,
                               long int,
                               long long int,
                               unsigned long int,
                               unsigned long long int,
                               char,
                               unsigned char,
                               RkFont,
                               RkColor,
                               RkPoint,
                               RkRealPoint,
                               RkSize,
                               RkPen,
                               Rk::Alignment>;


#endif // RK_VARIANT_H
