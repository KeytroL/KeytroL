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

#include "XmlKeyboardLayout.hpp"

#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <QtCore/QFile>
KL_RESTORE_WARNINGS


namespace KL
{

XmlKeyboardLayout::XmlKeyboardLayout(QObject * const parent)
    : QObject(parent)
{
}


bool XmlKeyboardLayout::load(const QUrl & fileUrl)
{
    QFile file{fileUrl.toLocalFile()};

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        return true;
    }

    return false;
}

} // namespace KL
