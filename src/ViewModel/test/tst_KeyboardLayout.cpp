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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
#include <QtTest/QSignalSpy>
KL_RESTORE_WARNINGS


using KL::ViewModel::KeyboardLayout;


namespace
{

KL::Model::KeyboardLayout createModelKeyboardLayout()
{
    KL::Model::KeyboardLayout modelKeyboardLayout;
    modelKeyboardLayout.replace(0,
        0,
        {KL::Model::ComputerKey{0, 0, 4, 4, "Esc", 1},
         KL::Model::ComputerKey{15, 22, 25, 4, "", 57}});
    return modelKeyboardLayout;
}


struct AbstractListModelSignalSpys
{
    AbstractListModelSignalSpys(QAbstractListModel * listModel)
        : rowsAboutToBeInserted(
              listModel, SIGNAL(rowsAboutToBeInserted(const QModelIndex &, int, int)))
        , rowsInserted(listModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)))
        , rowsAboutToBeRemoved(
              listModel, SIGNAL(rowsAboutToBeRemoved(const QModelIndex &, int, int)))
        , rowsRemoved(listModel, SIGNAL(rowsRemoved(const QModelIndex &, int, int)))
        , dataChanged(
              listModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)))
    {
    }

    QSignalSpy rowsAboutToBeInserted;
    QSignalSpy rowsInserted;
    QSignalSpy rowsAboutToBeRemoved;
    QSignalSpy rowsRemoved;
    QSignalSpy dataChanged;

    bool allCountsAreEqualTo(int count)
    {
        return rowsAboutToBeInserted.count() == count && rowsInserted.count() == count
            && rowsAboutToBeRemoved.count() == count && rowsRemoved.count() == count
            && dataChanged.count() == count;
    }
};

} // namespace


TEST_CASE("The underlying model can be changed", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;

    QSignalSpy modelAboutToBeResetSpy(&keyboardLayout, SIGNAL(modelAboutToBeReset()));
    QSignalSpy modelResetSpy(&keyboardLayout, SIGNAL(modelReset()));

    REQUIRE(keyboardLayout.model().computerKeys().size() == 0u);

    keyboardLayout.setModel(createModelKeyboardLayout());

    REQUIRE(modelAboutToBeResetSpy.count() == 1);
    REQUIRE(modelResetSpy.count() == 1);

    REQUIRE(keyboardLayout.model().computerKeys().size() == 2u);
    REQUIRE(keyboardLayout.model().computerKeys().at(0)
        == KL::Model::ComputerKey(0, 0, 4, 4, "Esc", 1));
    REQUIRE(keyboardLayout.model().computerKeys().at(1)
        == KL::Model::ComputerKey(15, 22, 25, 4, "", 57));
}


TEST_CASE("Adding a computer key always succeeds", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    const auto originalSize = keyboardLayout.model().computerKeys().size();
    AbstractListModelSignalSpys spys{&keyboardLayout};

    keyboardLayout.addComputerKey(88, 10, 4, 8, "+", 78);

    REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize + 1);
    REQUIRE(keyboardLayout.model().computerKeys().back()
        == KL::Model::ComputerKey(88, 10, 4, 8, "+", 78));

    REQUIRE(spys.rowsAboutToBeInserted.count() == 1);
    REQUIRE(spys.rowsInserted.count() == 1);
    REQUIRE(spys.rowsAboutToBeRemoved.count() == 0);
    REQUIRE(spys.rowsRemoved.count() == 0);
    REQUIRE(spys.dataChanged.count() == 0);
}


TEST_CASE("Removing a computer key", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    const auto originalSize = keyboardLayout.model().computerKeys().size();
    AbstractListModelSignalSpys spys{&keyboardLayout};

    SECTION("fails with an invalid model index")
    {
        keyboardLayout.removeComputerKey(keyboardLayout.modelIndex(2));

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().front()
            == KL::Model::ComputerKey(0, 0, 4, 4, "Esc", 1));

        REQUIRE(spys.allCountsAreEqualTo(0));
    }

    SECTION("succeeds with a valid model index")
    {
        keyboardLayout.removeComputerKey(keyboardLayout.modelIndex(0));

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize - 1);
        REQUIRE(keyboardLayout.model().computerKeys().front()
            == KL::Model::ComputerKey(15, 22, 25, 4, "", 57));

        REQUIRE(spys.rowsAboutToBeInserted.count() == 0);
        REQUIRE(spys.rowsInserted.count() == 0);
        REQUIRE(spys.rowsAboutToBeRemoved.count() == 1);
        REQUIRE(spys.rowsRemoved.count() == 1);
        REQUIRE(spys.dataChanged.count() == 0);
    }
}


TEST_CASE("Moving a computer key", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    const auto originalSize = keyboardLayout.model().computerKeys().size();
    AbstractListModelSignalSpys spys{&keyboardLayout};

    SECTION("fails with an invalid model index")
    {
        keyboardLayout.moveComputerKey(keyboardLayout.modelIndex(2), 23, 42);

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(15, 22, 25, 4, "", 57));

        REQUIRE(spys.allCountsAreEqualTo(0));
    }

    SECTION("succeeds with a valid model index")
    {
        keyboardLayout.moveComputerKey(keyboardLayout.modelIndex(1), 23, 42);

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(23, 42, 25, 4, "", 57));

        REQUIRE(spys.rowsAboutToBeInserted.count() == 1);
        REQUIRE(spys.rowsInserted.count() == 1);
        REQUIRE(spys.rowsAboutToBeRemoved.count() == 1);
        REQUIRE(spys.rowsRemoved.count() == 1);
        REQUIRE(spys.dataChanged.count() == 0);
    }
}


TEST_CASE("Renaming a computer key", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    const auto originalSize = keyboardLayout.model().computerKeys().size();
    AbstractListModelSignalSpys spys{&keyboardLayout};

    SECTION("fails with an invalid model index")
    {
        keyboardLayout.renameComputerKey(keyboardLayout.modelIndex(2), "A");

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(15, 22, 25, 4, "", 57));

        REQUIRE(spys.allCountsAreEqualTo(0));
    }

    SECTION("succeeds with a valid model index")
    {
        keyboardLayout.renameComputerKey(keyboardLayout.modelIndex(1), "A");

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(15, 22, 25, 4, "A", 57));

        REQUIRE(spys.rowsAboutToBeInserted.count() == 0);
        REQUIRE(spys.rowsInserted.count() == 0);
        REQUIRE(spys.rowsAboutToBeRemoved.count() == 0);
        REQUIRE(spys.rowsRemoved.count() == 0);
        REQUIRE(spys.dataChanged.count() == 1);
    }
}


TEST_CASE("Binding a computer key", "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    const auto originalSize = keyboardLayout.model().computerKeys().size();
    AbstractListModelSignalSpys spys{&keyboardLayout};

    SECTION("fails with an invalid model index")
    {
        keyboardLayout.bindComputerKey(keyboardLayout.modelIndex(2), 2);

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(15, 22, 25, 4, "", 57));

        REQUIRE(spys.allCountsAreEqualTo(0));
    }

    SECTION("succeeds with a valid model index")
    {
        keyboardLayout.bindComputerKey(keyboardLayout.modelIndex(1), 2);

        REQUIRE(keyboardLayout.model().computerKeys().size() == originalSize);
        REQUIRE(keyboardLayout.model().computerKeys().at(1)
            == KL::Model::ComputerKey(15, 22, 25, 4, "", 2));

        REQUIRE(spys.rowsAboutToBeInserted.count() == 0);
        REQUIRE(spys.rowsInserted.count() == 0);
        REQUIRE(spys.rowsAboutToBeRemoved.count() == 0);
        REQUIRE(spys.rowsRemoved.count() == 0);
        REQUIRE(spys.dataChanged.count() == 1);
    }
}


TEST_CASE("The abstract methods of QAbstractListModel are properly implemented",
    "[KeyboardLayout]")
{
    KeyboardLayout keyboardLayout;
    keyboardLayout.setModel(createModelKeyboardLayout());

    SECTION("rowCount()")
    {
        REQUIRE(keyboardLayout.rowCount(keyboardLayout.modelIndex(0)) == 0);
        REQUIRE(keyboardLayout.rowCount(keyboardLayout.modelIndex(1)) == 0);

        REQUIRE(keyboardLayout.rowCount({})
            == static_cast<int>(keyboardLayout.model().computerKeys().size()));
    }

    SECTION("data()")
    {
        REQUIRE(keyboardLayout.data({}, KeyboardLayout::XRole) == QVariant());

        const auto modelIndex = keyboardLayout.modelIndex(1);
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::XRole) == 15);
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::YRole) == 22);
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::WidthRole) == 25);
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::HeightRole) == 4);
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::LabelRole) == "");
        REQUIRE(keyboardLayout.data(modelIndex, KeyboardLayout::KeyCodeRole) == 57);

        REQUIRE(keyboardLayout.data(modelIndex, 42) == QVariant());
    }

    SECTION("roleNames()")
    {
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::XRole] == "x"));
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::YRole] == "y"));
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::WidthRole] == "width"));
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::HeightRole] == "height"));
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::LabelRole] == "label"));
        REQUIRE((keyboardLayout.roleNames()[KeyboardLayout::KeyCodeRole] == "keyCode"));
    }
}
