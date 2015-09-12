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

#include "KL/Core/Connection.hpp"


namespace KL
{

bool Connection::isConnected() const
{
    return *mConnected;
}


void Connection::disconnect() const
{
    *mConnected = false;
}


Connection::Connection(const std::shared_ptr<bool> connected)
    : mConnected(std::move(connected))
{
}

} // namespace KL
