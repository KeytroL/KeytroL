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

#include <memory>


namespace KL
{

template <typename T>
class Signal;


class Connection
{
public:
    bool isConnected() const;

    void disconnect() const;

private:
    template <typename T>
    friend class KL::Signal;

    Connection(std::shared_ptr<bool> connected);

    const std::shared_ptr<bool> mConnected;
};

} // namespace KL
