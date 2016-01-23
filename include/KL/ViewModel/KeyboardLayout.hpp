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

#pragma once

#include "KL/Core/NotifyingVector.hpp"
#include "KL/Model/ComputerKey.hpp"
#include "KL/Model/KeyboardLayout.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QAbstractListModel>
#include <QtCore/QModelIndex>
#include <QtCore/QString>
KL_RESTORE_WARNINGS


namespace KL
{
namespace ViewModel
{

class KeyboardLayout : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ComputerKeyRoles
    {
        XRole = Qt::UserRole + 1,
        YRole,
        WidthRole,
        HeightRole,
        LabelRole,
        KeyCodeRole,
    };

    KeyboardLayout(QObject * parent = nullptr);

    const Model::KeyboardLayout & model() const;
    void setModel(Model::KeyboardLayout model);

    Q_INVOKABLE void addComputerKey(int x,
        int y,
        unsigned int width,
        unsigned int height,
        const QString & label,
        unsigned int keyCode);

    Q_INVOKABLE void removeComputerKey(const QModelIndex & index);

    Q_INVOKABLE void moveComputerKey(const QModelIndex & index, int x, int y);

    Q_INVOKABLE void renameComputerKey(const QModelIndex & index, const QString & label);

    Q_INVOKABLE void bindComputerKey(const QModelIndex & index, unsigned int keyCode);

    Q_INVOKABLE QModelIndex modelIndex(int row) const;

    int rowCount(const QModelIndex & index) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    using ReplaceDiff = Core::NotifyingVector<Model::ComputerKey>::ReplaceDiff;

    void beforeModelReplace(const ReplaceDiff & replaceDiff);
    void afterModelReplace(const ReplaceDiff & replaceDiff);

    Model::KeyboardLayout mModel;
    Core::ScopedConnection mBeforeModelReplaceConnection;
    Core::ScopedConnection mAfterModelReplaceConnection;
};

} // namespace ViewModel
} // namespace KL
