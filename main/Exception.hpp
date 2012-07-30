#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

namespace Game {

class Exception {
public:
    Exception(const std::string& msg) :
	m_msg(msg)
    {
    }

    const std::string& getMsg() const {
	return m_msg;
    }

private:
    std::string m_msg;
};

} // Game

#endif // GAME_EXCEPTION_HPP
