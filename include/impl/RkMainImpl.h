/**
 * File name: RkMainXWin.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
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

#ifndef RK_MAIN_IMPL_H
#define RK_MAIN_IMPL_H

#include "RkMain.h"

class RkWidget;

#ifdef RK_OS_WIN
class RkEventQueueWin;
#elif RK_OS_MAC
#else
class RkEventQueueX;
#endif // RK_WIN_OS

class RkMain::RkMainImpl
{
 public:

        RkMainImpl(RkMain *interface);
        RkMainImpl(RkMain *interface, int argc, char **argv);
	virtual ~RkMainImpl();
        RkMainImpl(const RkMainImpl &other) = delete;
        RkMainImpl& operator=(const RkMainImpl &other) = delete;
        RkMainImpl(RkMainImpl &&other) = delete;
        RkMainImpl& operator=(RkMainImpl &&other) = delete;
	bool setTopLevelWindow(RkWidget* widget);
        RkWidget* topLevelWindow(void);
        std::shared_ptr<RkEventQueue> getEventQueue();
	int exec(bool block = true);

 private:
        RK_DECALRE_INTERFACE_PTR(RkMain)
        RkWidget* topWindow;
        std::shared_ptr<RkEventQueue> eventQueue;
};

#endif // RK_MAIN_XWIN_H
