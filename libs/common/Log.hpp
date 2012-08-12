// Copyright (C) 2012 by Kristian Rumberg <kristianrumberg@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef GAME_LOG_HPP
#define GAME_LOG_HPP

#include <iostream>

namespace Game {

class Log {
public:
    enum Level {
	Level_ERROR = 0,
	Level_INFO  = 1,
    };

    static Log& getInstance() {
	static Log log;
	return log;
    }

    void print(Level level, const std::string& msg) {
	if (level <= m_level) {
	    std::cout << msg << std::endl;
	}
    }

    void setThreshold(Level level) {
	m_level = level;
    }

private:
    Log() :
        m_level(Level_INFO) {
    }

    Level m_level;
};

} // Game

#endif // GAME_LOG_HPP
