#ifndef GAME_LOG_HPP
#define GAME_LOG_HPP

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
