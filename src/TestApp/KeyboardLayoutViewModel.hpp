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

#include "KL/Core/Connection.hpp"
#include "KL/Core/Warnings.hpp"
#include "KL/Keyboard/KeyboardLayout.hpp"

KL_DISABLE_WARNINGS
#include <QtCore/QAbstractListModel>
KL_RESTORE_WARNINGS


namespace KL
{

class KeyboardLayoutViewModel : public QAbstractListModel
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

    KeyboardLayoutViewModel(QObject * parent = nullptr);

    Q_INVOKABLE void addComputerKey(int x,
        int y,
        unsigned int width,
        unsigned int height,
        const QString & label,
        unsigned int keyCode);

    Q_INVOKABLE void removeComputerKey(const QModelIndex & index);

    int rowCount(const QModelIndex & index) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    KeyboardLayout mModel;

    ScopedConnection mComputerKeyAboutToBeAddedConnection;
    ScopedConnection mComputerKeyAddedConnection;
    ScopedConnection mComputerKeyAboutToBeRemovedConnection;
    ScopedConnection mComputerKeyRemovedConnection;
};

} // namespace KL
