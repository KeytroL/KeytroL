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
public:
    KeyboardLayoutViewModel(KeyboardLayout & model, QObject * parent = nullptr);

    int rowCount(const QModelIndex & index) const override;
    QVariant data(const QModelIndex & index, int role) const override;

private:
    KeyboardLayout & mModel;

    ScopedConnection mComputerKeyAboutToBeAddedConnection;
    ScopedConnection mComputerKeyAddedConnection;
    ScopedConnection mComputerKeyAboutToBeRemovedConnection;
    ScopedConnection mComputerKeyRemovedConnection;
};

} // namespace KL
