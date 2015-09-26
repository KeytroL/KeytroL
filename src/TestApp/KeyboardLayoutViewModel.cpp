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

KeyboardLayoutViewModel::KeyboardLayoutViewModel(QObject * parent)
    : QAbstractListModel(parent)
{
    setModel(KeyboardLayout());
}


const KeyboardLayout & KeyboardLayoutViewModel::model() const
{
    return mModel;
}


void KeyboardLayoutViewModel::setModel(KeyboardLayout model)
{
    beginResetModel();
    mModel = std::move(model);
    endResetModel();

    mModel.beforeReplace().connect(
        [this](const NotifyingVector<ComputerKey>::Notification & notification)
        {
            beforeModelReplace(notification);
        });

    mModel.afterReplace().connect(
        [this](const NotifyingVector<ComputerKey>::Notification & notification)
        {
            afterModelReplace(notification);
        });
}


void KeyboardLayoutViewModel::addComputerKey(int x,
    int y,
    unsigned int width,
    unsigned int height,
    const QString & label,
    unsigned int keyCode)
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


void KeyboardLayoutViewModel::moveComputerKey(const QModelIndex & index, int x, int y)
{
    if (index.isValid())
    {
        const auto computerKeyIndex = static_cast<KeyboardLayout::SizeType>(index.row());
        auto computerKey = ComputerKey(mModel.computerKeys().at(computerKeyIndex), x, y);

        mModel.removeComputerKey(computerKeyIndex);
        mModel.addComputerKey(std::move(computerKey));
    }
}


void KeyboardLayoutViewModel::renameComputerKey(
    const QModelIndex & index, const QString & label)
{
    if (index.isValid())
    {
        const auto computerKeyIndex = static_cast<KeyboardLayout::SizeType>(index.row());
        mModel.replace(computerKeyIndex,
            computerKeyIndex + 1,
            {ComputerKey(
                mModel.computerKeys().at(computerKeyIndex), label.toStdString())});
    }
}


void KeyboardLayoutViewModel::bindComputerKey(
    const QModelIndex & index, Keyboard::KeyCode keyCode)
{
    if (index.isValid())
    {
        const auto computerKeyIndex = static_cast<KeyboardLayout::SizeType>(index.row());
        mModel.replace(computerKeyIndex,
            computerKeyIndex + 1,
            {ComputerKey(mModel.computerKeys().at(computerKeyIndex), keyCode)});
    }
}


QModelIndex KeyboardLayoutViewModel::modelIndex(int row) const
{
    return index(row, 0);
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


void KeyboardLayoutViewModel::beforeModelReplace(
    const NotifyingVector<ComputerKey>::Notification & notification)
{
    const auto newLast = notification.first + notification.replacementSize;

    if (newLast > notification.last)
    {
        beginInsertRows(QModelIndex(),
            static_cast<int>(notification.last),
            static_cast<int>(newLast - 1));
    }
    else if (newLast < notification.last)
    {
        beginRemoveRows(QModelIndex(),
            static_cast<int>(newLast),
            static_cast<int>(notification.last - 1));
    }
}


void KeyboardLayoutViewModel::afterModelReplace(
    const NotifyingVector<ComputerKey>::Notification & notification)
{
    const auto newLast = notification.first + notification.replacementSize;

    if (newLast > notification.last)
    {
        endInsertRows();
    }
    else if (newLast < notification.last)
    {
        endRemoveRows();
    }

    if ((notification.first != notification.last) && notification.replacementSize != 0)
    {
        dataChanged(modelIndex(static_cast<int>(notification.first)),
            modelIndex(static_cast<int>(std::min(notification.last, newLast) - 1)));
    }
}

} // namespace KL
