#ifndef COMMON_EXCEPTION_HPP
#define COMMON_EXCEPTION_HPP

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

#endif // COMMON_EXCEPTION_HPP
