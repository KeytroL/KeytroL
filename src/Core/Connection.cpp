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

Connection::Connection(Connection && other)
    : mConnected(std::move(other.mConnected))
{
}


Connection & Connection::operator=(Connection && other)
{
    mConnected = std::move(other.mConnected);
    return *this;
}


bool Connection::isConnected() const
{
    return mConnected && *mConnected;
}


void Connection::disconnect() const
{
    if (mConnected)
    {
        *mConnected = false;
    }
}


Connection::Connection(const std::shared_ptr<bool> connected)
    : mConnected(std::move(connected))
{
}


ScopedConnection::ScopedConnection(const Connection & other)
    : Connection(other)
{
}


ScopedConnection::~ScopedConnection()
{
    Connection::disconnect();
}


ScopedConnection::ScopedConnection(ScopedConnection && other)
    : Connection(std::move(other))
{
}


ScopedConnection & ScopedConnection::operator=(ScopedConnection && other)
{
    Connection::operator=(std::move(other));
    return *this;
}


ScopedConnection & ScopedConnection::operator=(const Connection & other)
{
    Connection::operator=(other);
    return *this;
}

} // namespace KL
