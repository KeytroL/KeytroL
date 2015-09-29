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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QObject>
#include <QtCore/QUrl>
KL_RESTORE_WARNINGS


namespace KL
{
namespace ViewModel
{

class KeyboardLayoutViewModel;


class XmlKeyboardLayout : public QObject
{
    Q_OBJECT

public:
    XmlKeyboardLayout(QObject * parent = nullptr);

    Q_INVOKABLE bool load(const QUrl & fileUrl,
        KL::ViewModel::KeyboardLayoutViewModel * keyboardLayoutViewModel);

    Q_INVOKABLE bool save(const QUrl & fileUrl,
        KL::ViewModel::KeyboardLayoutViewModel * keyboardLayoutViewModel);
};

} // namespace ViewModel
} // namespace KL
