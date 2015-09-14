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

KeyboardLayoutViewModel::KeyboardLayoutViewModel(QObject * const parent)
    : QAbstractListModel(parent)
{
    mComputerKeyAboutToBeAddedConnection = mModel.computerKeyAboutToBeAdded().connect(
        [this](const KeyboardLayout::SizeType index)
        {
            beginInsertRows(
                QModelIndex(), static_cast<int>(index), static_cast<int>(index));
        });

    mComputerKeyAddedConnection =
        mModel.computerKeyAdded().connect([this](const KeyboardLayout::SizeType)
            {
                endInsertRows();
            });

    mComputerKeyAboutToBeRemovedConnection = mModel.computerKeyAboutToBeRemoved().connect(
        [this](const KeyboardLayout::SizeType index)
        {
            beginRemoveRows(
                QModelIndex(), static_cast<int>(index), static_cast<int>(index));
        });

    mComputerKeyRemovedConnection =
        mModel.computerKeyRemoved().connect([this](const KeyboardLayout::SizeType)
            {
                endRemoveRows();
            });
}


void KeyboardLayoutViewModel::addComputerKey(const int x,
    const int y,
    const unsigned int width,
    const unsigned int height,
    const QString & label,
    const unsigned int keyCode)
{
    mModel.addComputerKey(ComputerKey(x, y, width, height, label.toStdString(), keyCode));
}


void KeyboardLayoutViewModel::removeComputerKey(const QModelIndex & index)
{
    if (index.isValid())
    {
        mModel.removeComputerKey(static_cast<KeyboardLayout::SizeType>(index.row()));
    }
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

    const auto & computerKey =
        mModel.computerKeys().at(static_cast<KeyboardLayout::SizeType>(index.row()));

    if (role == XRole)
    {
        return computerKey.x();
    }
    else if (role == YRole)
    {
        return computerKey.y();
    }
    else if (role == WidthRole)
    {
        return computerKey.width();
    }
    else if (role == HeightRole)
    {
        return computerKey.height();
    }
    else if (role == LabelRole)
    {
        return QString::fromStdString(computerKey.label());
    }
    else if (role == KeyCodeRole)
    {
        return computerKey.keyCode();
    }

    return {};
}


QHash<int, QByteArray> KeyboardLayoutViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XRole] = "x";
    roles[YRole] = "y";
    roles[WidthRole] = "width";
    roles[HeightRole] = "height";
    roles[LabelRole] = "label";
    roles[KeyCodeRole] = "keyCode";
    return roles;
}

} // namespace KL
