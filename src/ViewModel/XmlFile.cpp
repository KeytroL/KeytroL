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

#include "KL/ViewModel/XmlFile.hpp"

#include "KL/Model/KeyboardLayout.hpp"
#include "KL/ViewModel/KeyboardLayout.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>
KL_RESTORE_WARNINGS


namespace KL
{
namespace ViewModel
{

XmlFile::XmlFile(QObject * parent)
    : QObject(parent)
{
}


bool XmlFile::load(const QUrl & fileUrl, KeyboardLayout * keyboardLayout)
{
    if (!keyboardLayout)
    {
        return false;
    }

    QFile file{fileUrl.toLocalFile()};

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader xml{&file};
        Model::KeyboardLayout modelKeyboardLayout;

        if (xml.readNextStartElement() && xml.name() == "KeyboardLayout")
        {
            while (!xml.atEnd())
            {
                if (xml.readNext() == QXmlStreamReader::StartElement
                    && xml.name() == "ComputerKey")
                {
                    const auto & attributes = xml.attributes();

                    modelKeyboardLayout.addComputerKey(
                        Model::ComputerKey(attributes.value("x").toInt(),
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
            keyboardLayout->setModel(std::move(modelKeyboardLayout));
            return true;
        }
    }

    return false;
}


bool XmlFile::save(const QUrl & fileUrl, KeyboardLayout * keyboardLayout)
{
    if (!keyboardLayout)
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

        for (const auto & computerKey : keyboardLayout->model().computerKeys())
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

} // namespace ViewModel
} // namespace KL
