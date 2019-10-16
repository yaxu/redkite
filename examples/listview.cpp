/**
 * File name: listview.cpp
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

#include "RkMain.h"
#include "RkLog.h"
#include "RkModel.h"
#include "RkListView.h"
#include "RkModel.h"

class MyModel: public RkModel {
  public:
        MyModel(RkEventQueue *eventQueue) : RkModel(eventQueue)
                                          , currentIndex{-1}
        {
        }

       void setData(std::vector<std::string> &list)
       {
               stringList = list;
               action updated();
       }

       RkVariant data(int index, RkModel::DataType type) const final
       {
               if (stringList.empty() || index > stringList.size() - 1 || index < 0)
                       return RkVariant();

               if (type == RkModel::DataType::Text)
                       return RkVariant(stringList[index]);

               if (type == RkModel::DataType::Color && index == selectedIndex())
                       return RkVariant(RkColor(255, 255, 255));

               if (type == RkModel::DataType::Background && index == selectedIndex())
                       return RkVariant(RkColor(100, 100, 200));

               return RkVariant();
       }

       size_t rows() const final
       {
               return stringList.size();
       }

        void selectIndex(int index) final { currentIndex = index; }
        int selectedIndex() const final { return currentIndex; }

private:
        std::vector<std::string> stringList;
        int currentIndex;
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);
    auto widget = new RkWidget(&app);
    widget->setTitle("Listview Example");
    widget->setSize({250, 400});

    auto listViewWidget = new RkListView(widget);
    listViewWidget->setTitle("Listview Widget");
    //    listViewWidget->setBackgroundColor({100, 100, 100});
    listViewWidget->setSize(widget->size());


    auto model = std::make_unique<MyModel>(app.eventQueue());
    std::vector<std::string> data;
    for (int i = 0; i < 100; i++)
            data.emplace_back("row " + std::to_string(i));

    model->setData(data);
    listViewWidget->setModel(model.get());
    widget->show();

    return app.exec();
}
