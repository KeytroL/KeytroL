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

#include "KL/ViewModel/KeyboardLayout.hpp"


namespace KL
{
namespace ViewModel
{

KeyboardLayout::KeyboardLayout(QObject * parent)
    : QAbstractListModel(parent)
{
    setModel(Model::KeyboardLayout());
}


const Model::KeyboardLayout & KeyboardLayout::model() const
{
    return mModel;
}


void KeyboardLayout::setModel(Model::KeyboardLayout model)
{
    mBeforeModelReplaceConnection.disconnect();
    mAfterModelReplaceConnection.disconnect();

    beginResetModel();
    mModel = std::move(model);
    endResetModel();

    mBeforeModelReplaceConnection =
        mModel.beforeReplace().connect([this](const ReplaceDiff & replaceDiff)
            {
                beforeModelReplace(replaceDiff);
            });

    mAfterModelReplaceConnection =
        mModel.afterReplace().connect([this](const ReplaceDiff & replaceDiff)
            {
                afterModelReplace(replaceDiff);
            });
}


void KeyboardLayout::addComputerKey(int x,
    int y,
    unsigned int width,
    unsigned int height,
    const QString & label,
    unsigned int keyCode)
{
    mModel.addComputerKey(
        Model::ComputerKey(x, y, width, height, label.toStdString(), keyCode));
}


void KeyboardLayout::removeComputerKey(const QModelIndex & index)
{
    if (index.model() != this || !index.isValid())
    {
        return;
    }

    mModel.removeComputerKey(static_cast<Model::KeyboardLayout::SizeType>(index.row()));
}


void KeyboardLayout::moveComputerKey(const QModelIndex & index, int x, int y)
{
    if (index.model() != this || !index.isValid())
    {
        return;
    }

    const auto computerKeyIndex =
        static_cast<Model::KeyboardLayout::SizeType>(index.row());
    auto computerKey =
        Model::ComputerKey(mModel.computerKeys().at(computerKeyIndex), x, y);

    mModel.removeComputerKey(computerKeyIndex);
    mModel.addComputerKey(std::move(computerKey));
}


void KeyboardLayout::renameComputerKey(const QModelIndex & index, const QString & label)
{
    if (index.model() != this || !index.isValid())
    {
        return;
    }

    const auto computerKeyIndex =
        static_cast<Model::KeyboardLayout::SizeType>(index.row());
    mModel.replace(computerKeyIndex,
        computerKeyIndex + 1,
        {Model::ComputerKey(
            mModel.computerKeys().at(computerKeyIndex), label.toStdString())});
}


void KeyboardLayout::bindComputerKey(
    const QModelIndex & index, IO::KeyboardInput::KeyCode keyCode)
{
    if (index.model() != this || !index.isValid())
    {
        return;
    }

    const auto computerKeyIndex =
        static_cast<Model::KeyboardLayout::SizeType>(index.row());
    mModel.replace(computerKeyIndex,
        computerKeyIndex + 1,
        {Model::ComputerKey(mModel.computerKeys().at(computerKeyIndex), keyCode)});
}


QModelIndex KeyboardLayout::modelIndex(int row) const
{
    return index(row, 0);
}


int KeyboardLayout::rowCount(const QModelIndex & index) const
{
    if (index.isValid())
    {
        return 0;
    }

    return static_cast<int>(mModel.computerKeys().size());
}


QVariant KeyboardLayout::data(const QModelIndex & index, int role) const
{
    if (index.model() != this || !index.isValid())
    {
        return {};
    }

    const auto & computerKey = mModel.computerKeys().at(
        static_cast<Model::KeyboardLayout::SizeType>(index.row()));

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


QHash<int, QByteArray> KeyboardLayout::roleNames() const
{
    return {{XRole, "x"},
        {YRole, "y"},
        {WidthRole, "width"},
        {HeightRole, "height"},
        {LabelRole, "label"},
        {KeyCodeRole, "keyCode"}};
}


void KeyboardLayout::beforeModelReplace(const ReplaceDiff & replaceDiff)
{
    const auto newLast = replaceDiff.first + replaceDiff.replacementSize;

    if (newLast > replaceDiff.last)
    {
        beginInsertRows(QModelIndex(),
            static_cast<int>(replaceDiff.last),
            static_cast<int>(newLast - 1));
    }
    else if (newLast < replaceDiff.last)
    {
        beginRemoveRows(QModelIndex(),
            static_cast<int>(newLast),
            static_cast<int>(replaceDiff.last - 1));
    }
}


void KeyboardLayout::afterModelReplace(const ReplaceDiff & replaceDiff)
{
    const auto newLast = replaceDiff.first + replaceDiff.replacementSize;

    if (newLast > replaceDiff.last)
    {
        endInsertRows();
    }
    else if (newLast < replaceDiff.last)
    {
        endRemoveRows();
    }

    if ((replaceDiff.first != replaceDiff.last) && (replaceDiff.replacementSize != 0))
    {
        dataChanged(modelIndex(static_cast<int>(replaceDiff.first)),
            modelIndex(static_cast<int>(std::min(replaceDiff.last, newLast) - 1)));
    }
}

} // namespace ViewModel
} // namespace KL
