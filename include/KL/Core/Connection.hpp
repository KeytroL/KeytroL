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
namespace Core
{

template <typename T>
class Signal;


class Connection
{
public:
    Connection() = default;
    Connection(const Connection & other) = default;
    Connection & operator=(const Connection & other) = default;

    Connection(Connection && other);
    Connection & operator=(Connection && other);

    bool isConnected() const;

    void disconnect() const;

private:
    template <typename T>
    friend class KL::Core::Signal;

    explicit Connection(std::shared_ptr<bool> connected);

    std::shared_ptr<bool> mConnected;
};


class ScopedConnection : public Connection
{
public:
    ScopedConnection() = default;
    ~ScopedConnection();

    ScopedConnection(ScopedConnection && other);
    ScopedConnection & operator=(ScopedConnection && other);

    ScopedConnection(const Connection & other);
    ScopedConnection & operator=(const Connection & other);
};

} // namespace Core
} // namespace KL
