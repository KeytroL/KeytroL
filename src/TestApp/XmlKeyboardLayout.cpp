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

#include "KeyboardLayoutViewModel.hpp"

#include "KL/Keyboard/KeyboardLayout.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>
KL_RESTORE_WARNINGS


namespace KL
{

XmlKeyboardLayout::XmlKeyboardLayout(QObject * parent)
    : QObject(parent)
{
}


bool XmlKeyboardLayout::load(
    const QUrl & fileUrl, KeyboardLayoutViewModel * keyboardLayoutViewModel)
{
    if (!keyboardLayoutViewModel)
    {
        return false;
    }

    QFile file{fileUrl.toLocalFile()};

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader xml{&file};
        KeyboardLayout keyboardLayout;

        if (xml.readNextStartElement() && xml.name() == "KeyboardLayout")
        {
            while (!xml.atEnd())
            {
                if (xml.readNext() == QXmlStreamReader::StartElement
                    && xml.name() == "ComputerKey")
                {
                    const auto & attributes = xml.attributes();

                    keyboardLayout.addComputerKey(
                        ComputerKey(attributes.value("x").toInt(),
                            attributes.value("y").toInt(),
                            attributes.value("width").toUInt(),
                            attributes.value("height").toUInt(),
                            attributes.value("label").toString().toStdString(),
                            attributes.value("keyCode").toUInt()));
                }
            }
        }

        if (!xml.hasError())
        {
            keyboardLayoutViewModel->setModel(std::move(keyboardLayout));
            return true;
        }
    }

    return false;
}


bool XmlKeyboardLayout::save(
    const QUrl & fileUrl, KeyboardLayoutViewModel * keyboardLayoutViewModel)
{
    if (!keyboardLayoutViewModel)
    {
        return false;
    }

    QFile file{fileUrl.toLocalFile()};

    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QXmlStreamWriter xml{&file};
        xml.setAutoFormatting(true);

        xml.writeStartDocument();
        xml.writeStartElement("KeyboardLayout");

        for (const auto & computerKey : keyboardLayoutViewModel->model().computerKeys())
        {
            xml.writeStartElement("ComputerKey");
            xml.writeAttribute("x", QString::number(computerKey.x()));
            xml.writeAttribute("y", QString::number(computerKey.y()));
            xml.writeAttribute("width", QString::number(computerKey.width()));
            xml.writeAttribute("height", QString::number(computerKey.height()));
            xml.writeAttribute("label", QString::fromStdString(computerKey.label()));
            xml.writeAttribute("keyCode", QString::number(computerKey.keyCode()));
            xml.writeEndElement();
        }

        xml.writeEndElement();
        xml.writeEndDocument();

        if (!xml.hasError())
        {
            return true;
        }
    }

    return false;
}

} // namespace KL
