// KeytroL
// Copyright (C) 2015 Alain Martin
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "KeyboardLayoutViewModel.hpp"


namespace KL
{

KeyboardLayoutViewModel::KeyboardLayoutViewModel(
    const KeyboardLayout & model, QObject * const parent)
    : QAbstractListModel(parent)
    , mModel(model)
{
}


int KeyboardLayoutViewModel::rowCount(const QModelIndex & index) const
{
    if (index.isValid())
    {
        return 0;
    }

    return static_cast<int>(mModel.computerKeys().size());
}


QVariant KeyboardLayoutViewModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    if (role == Qt::DisplayRole)
    {
        using SizeType =
            std::remove_reference<decltype(mModel.computerKeys())>::type::size_type;
        const auto & computerKey =
            mModel.computerKeys().at(static_cast<SizeType>(index.row()));

        return QString("%1, %2, %3, %4, %5, %6")
            .arg(computerKey.x())
            .arg(computerKey.y())
            .arg(computerKey.width())
            .arg(computerKey.height())
            .arg(QString::fromStdString(computerKey.label()))
            .arg(computerKey.keyCode());
    }

    return {};
}

} // namespace KL
