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

#include "KL/IO/KeyboardInput.hpp"

#include <functional>
#include <map>
#include <utility>


namespace KL
{
namespace Model
{

class KeyboardMapping
{
    using Code = IO::KeyboardInput::KeyCode;
    using State = IO::KeyboardInput::KeyState;

public:
    std::function<void()> & at(Code keyCode, State keyState);
    const std::function<void()> & at(Code keyCode, State keyState) const;

private:
    std::map<std::pair<Code, State>, std::function<void()>> mKeyToFunction;
};

} // namespace Model
} // namespace KL
