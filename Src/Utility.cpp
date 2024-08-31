#include <Utility.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>


size_t	toInt(std::string s) {
	//No need for negative numbers in tetris game
	if (s[0] == '-') {
		s.erase(0,1);
	}
	size_t res = 0;
	for (auto it = s.begin(); it != s.end(); ++it) {
		res = res * 10 + (*it) - '0';
	}
	return res;
}

std::string	 toString(Music::ID id) {
	if (id == Music::Distance)
		return "Distance";
	else if (id == Music::MirrorOfEdge)
		return "Mirror Of Edge";
	else
		return "Track In Time";
}


std::string toString(sf::Keyboard::Key key)
{
#define BOOK_KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		BOOK_KEYTOSTRING_CASE(Unknown)
			BOOK_KEYTOSTRING_CASE(A)
			BOOK_KEYTOSTRING_CASE(B)
			BOOK_KEYTOSTRING_CASE(C)
			BOOK_KEYTOSTRING_CASE(D)
			BOOK_KEYTOSTRING_CASE(E)
			BOOK_KEYTOSTRING_CASE(F)
			BOOK_KEYTOSTRING_CASE(G)
			BOOK_KEYTOSTRING_CASE(H)
			BOOK_KEYTOSTRING_CASE(I)
			BOOK_KEYTOSTRING_CASE(J)
			BOOK_KEYTOSTRING_CASE(K)
			BOOK_KEYTOSTRING_CASE(L)
			BOOK_KEYTOSTRING_CASE(M)
			BOOK_KEYTOSTRING_CASE(N)
			BOOK_KEYTOSTRING_CASE(O)
			BOOK_KEYTOSTRING_CASE(P)
			BOOK_KEYTOSTRING_CASE(Q)
			BOOK_KEYTOSTRING_CASE(R)
			BOOK_KEYTOSTRING_CASE(S)
			BOOK_KEYTOSTRING_CASE(T)
			BOOK_KEYTOSTRING_CASE(U)
			BOOK_KEYTOSTRING_CASE(V)
			BOOK_KEYTOSTRING_CASE(W)
			BOOK_KEYTOSTRING_CASE(X)
			BOOK_KEYTOSTRING_CASE(Y)
			BOOK_KEYTOSTRING_CASE(Z)
			BOOK_KEYTOSTRING_CASE(Num0)
			BOOK_KEYTOSTRING_CASE(Num1)
			BOOK_KEYTOSTRING_CASE(Num2)
			BOOK_KEYTOSTRING_CASE(Num3)
			BOOK_KEYTOSTRING_CASE(Num4)
			BOOK_KEYTOSTRING_CASE(Num5)
			BOOK_KEYTOSTRING_CASE(Num6)
			BOOK_KEYTOSTRING_CASE(Num7)
			BOOK_KEYTOSTRING_CASE(Num8)
			BOOK_KEYTOSTRING_CASE(Num9)
			BOOK_KEYTOSTRING_CASE(Escape)
			BOOK_KEYTOSTRING_CASE(LControl)
			BOOK_KEYTOSTRING_CASE(LShift)
			BOOK_KEYTOSTRING_CASE(LAlt)
			BOOK_KEYTOSTRING_CASE(LSystem)
			BOOK_KEYTOSTRING_CASE(RControl)
			BOOK_KEYTOSTRING_CASE(RShift)
			BOOK_KEYTOSTRING_CASE(RAlt)
			BOOK_KEYTOSTRING_CASE(RSystem)
			BOOK_KEYTOSTRING_CASE(Menu)
			BOOK_KEYTOSTRING_CASE(LBracket)
			BOOK_KEYTOSTRING_CASE(RBracket)
			BOOK_KEYTOSTRING_CASE(SemiColon)
			BOOK_KEYTOSTRING_CASE(Comma)
			BOOK_KEYTOSTRING_CASE(Period)
			BOOK_KEYTOSTRING_CASE(Quote)
			BOOK_KEYTOSTRING_CASE(Slash)
			BOOK_KEYTOSTRING_CASE(BackSlash)
			BOOK_KEYTOSTRING_CASE(Tilde)
			BOOK_KEYTOSTRING_CASE(Equal)
			BOOK_KEYTOSTRING_CASE(Dash)
			BOOK_KEYTOSTRING_CASE(Space)
			BOOK_KEYTOSTRING_CASE(Return)
			BOOK_KEYTOSTRING_CASE(BackSpace)
			BOOK_KEYTOSTRING_CASE(Tab)
			BOOK_KEYTOSTRING_CASE(PageUp)
			BOOK_KEYTOSTRING_CASE(PageDown)
			BOOK_KEYTOSTRING_CASE(End)
			BOOK_KEYTOSTRING_CASE(Home)
			BOOK_KEYTOSTRING_CASE(Insert)
			BOOK_KEYTOSTRING_CASE(Delete)
			BOOK_KEYTOSTRING_CASE(Add)
			BOOK_KEYTOSTRING_CASE(Subtract)
			BOOK_KEYTOSTRING_CASE(Multiply)
			BOOK_KEYTOSTRING_CASE(Divide)
			BOOK_KEYTOSTRING_CASE(Left)
			BOOK_KEYTOSTRING_CASE(Right)
			BOOK_KEYTOSTRING_CASE(Up)
			BOOK_KEYTOSTRING_CASE(Down)
			BOOK_KEYTOSTRING_CASE(Numpad0)
			BOOK_KEYTOSTRING_CASE(Numpad1)
			BOOK_KEYTOSTRING_CASE(Numpad2)
			BOOK_KEYTOSTRING_CASE(Numpad3)
			BOOK_KEYTOSTRING_CASE(Numpad4)
			BOOK_KEYTOSTRING_CASE(Numpad5)
			BOOK_KEYTOSTRING_CASE(Numpad6)
			BOOK_KEYTOSTRING_CASE(Numpad7)
			BOOK_KEYTOSTRING_CASE(Numpad8)
			BOOK_KEYTOSTRING_CASE(Numpad9)
			BOOK_KEYTOSTRING_CASE(F1)
			BOOK_KEYTOSTRING_CASE(F2)
			BOOK_KEYTOSTRING_CASE(F3)
			BOOK_KEYTOSTRING_CASE(F4)
			BOOK_KEYTOSTRING_CASE(F5)
			BOOK_KEYTOSTRING_CASE(F6)
			BOOK_KEYTOSTRING_CASE(F7)
			BOOK_KEYTOSTRING_CASE(F8)
			BOOK_KEYTOSTRING_CASE(F9)
			BOOK_KEYTOSTRING_CASE(F10)
			BOOK_KEYTOSTRING_CASE(F11)
			BOOK_KEYTOSTRING_CASE(F12)
			BOOK_KEYTOSTRING_CASE(F13)
			BOOK_KEYTOSTRING_CASE(F14)
			BOOK_KEYTOSTRING_CASE(F15)
			BOOK_KEYTOSTRING_CASE(Pause)
	}

	return "";
}
namespace utility {
#define BOOK_STRINGTOKEY_CASE(KEY) {#KEY,sf::Keyboard::KEY},
	std::map<std::string, sf::Keyboard::Key>keyMap = {
			BOOK_STRINGTOKEY_CASE(Unknown)
			BOOK_STRINGTOKEY_CASE(A)
			BOOK_STRINGTOKEY_CASE(B)
			BOOK_STRINGTOKEY_CASE(C)
			BOOK_STRINGTOKEY_CASE(D)
			BOOK_STRINGTOKEY_CASE(E)
			BOOK_STRINGTOKEY_CASE(F)
			BOOK_STRINGTOKEY_CASE(G)
			BOOK_STRINGTOKEY_CASE(H)
			BOOK_STRINGTOKEY_CASE(I)
			BOOK_STRINGTOKEY_CASE(J)
			BOOK_STRINGTOKEY_CASE(K)
			BOOK_STRINGTOKEY_CASE(L)
			BOOK_STRINGTOKEY_CASE(M)
			BOOK_STRINGTOKEY_CASE(N)
			BOOK_STRINGTOKEY_CASE(O)
			BOOK_STRINGTOKEY_CASE(P)
			BOOK_STRINGTOKEY_CASE(Q)
			BOOK_STRINGTOKEY_CASE(R)
			BOOK_STRINGTOKEY_CASE(S)
			BOOK_STRINGTOKEY_CASE(T)
			BOOK_STRINGTOKEY_CASE(U)
			BOOK_STRINGTOKEY_CASE(V)
			BOOK_STRINGTOKEY_CASE(W)
			BOOK_STRINGTOKEY_CASE(X)
			BOOK_STRINGTOKEY_CASE(Y)
			BOOK_STRINGTOKEY_CASE(Z)
			BOOK_STRINGTOKEY_CASE(Num0)
			BOOK_STRINGTOKEY_CASE(Num1)
			BOOK_STRINGTOKEY_CASE(Num2)
			BOOK_STRINGTOKEY_CASE(Num3)
			BOOK_STRINGTOKEY_CASE(Num4)
			BOOK_STRINGTOKEY_CASE(Num5)
			BOOK_STRINGTOKEY_CASE(Num6)
			BOOK_STRINGTOKEY_CASE(Num7)
			BOOK_STRINGTOKEY_CASE(Num8)
			BOOK_STRINGTOKEY_CASE(Num9)
			BOOK_STRINGTOKEY_CASE(Escape)
			BOOK_STRINGTOKEY_CASE(LControl)
			BOOK_STRINGTOKEY_CASE(LShift)
			BOOK_STRINGTOKEY_CASE(LAlt)
			BOOK_STRINGTOKEY_CASE(LSystem)
			BOOK_STRINGTOKEY_CASE(RControl)
			BOOK_STRINGTOKEY_CASE(RShift)
			BOOK_STRINGTOKEY_CASE(RAlt)
			BOOK_STRINGTOKEY_CASE(RSystem)
			BOOK_STRINGTOKEY_CASE(Menu)
			BOOK_STRINGTOKEY_CASE(LBracket)
			BOOK_STRINGTOKEY_CASE(RBracket)
			BOOK_STRINGTOKEY_CASE(SemiColon)
			BOOK_STRINGTOKEY_CASE(Comma)
			BOOK_STRINGTOKEY_CASE(Period)
			BOOK_STRINGTOKEY_CASE(Quote)
			BOOK_STRINGTOKEY_CASE(Slash)
			BOOK_STRINGTOKEY_CASE(BackSlash)
			BOOK_STRINGTOKEY_CASE(Tilde)
			BOOK_STRINGTOKEY_CASE(Equal)
			BOOK_STRINGTOKEY_CASE(Dash)
			BOOK_STRINGTOKEY_CASE(Space)
			BOOK_STRINGTOKEY_CASE(Return)
			BOOK_STRINGTOKEY_CASE(BackSpace)
			BOOK_STRINGTOKEY_CASE(Tab)
			BOOK_STRINGTOKEY_CASE(PageUp)
			BOOK_STRINGTOKEY_CASE(PageDown)
			BOOK_STRINGTOKEY_CASE(End)
			BOOK_STRINGTOKEY_CASE(Home)
			BOOK_STRINGTOKEY_CASE(Insert)
			BOOK_STRINGTOKEY_CASE(Delete)
			BOOK_STRINGTOKEY_CASE(Add)
			BOOK_STRINGTOKEY_CASE(Subtract)
			BOOK_STRINGTOKEY_CASE(Multiply)
			BOOK_STRINGTOKEY_CASE(Divide)
			BOOK_STRINGTOKEY_CASE(Left)
			BOOK_STRINGTOKEY_CASE(Right)
			BOOK_STRINGTOKEY_CASE(Up)
			BOOK_STRINGTOKEY_CASE(Down)
			BOOK_STRINGTOKEY_CASE(Numpad0)
			BOOK_STRINGTOKEY_CASE(Numpad1)
			BOOK_STRINGTOKEY_CASE(Numpad2)
			BOOK_STRINGTOKEY_CASE(Numpad3)
			BOOK_STRINGTOKEY_CASE(Numpad4)
			BOOK_STRINGTOKEY_CASE(Numpad5)
			BOOK_STRINGTOKEY_CASE(Numpad6)
			BOOK_STRINGTOKEY_CASE(Numpad7)
			BOOK_STRINGTOKEY_CASE(Numpad8)
			BOOK_STRINGTOKEY_CASE(Numpad9)
			BOOK_STRINGTOKEY_CASE(F1)
			BOOK_STRINGTOKEY_CASE(F2)
			BOOK_STRINGTOKEY_CASE(F3)
			BOOK_STRINGTOKEY_CASE(F4)
			BOOK_STRINGTOKEY_CASE(F5)
			BOOK_STRINGTOKEY_CASE(F6)
			BOOK_STRINGTOKEY_CASE(F7)
			BOOK_STRINGTOKEY_CASE(F8)
			BOOK_STRINGTOKEY_CASE(F9)
			BOOK_STRINGTOKEY_CASE(F10)
			BOOK_STRINGTOKEY_CASE(F11)
			BOOK_STRINGTOKEY_CASE(F12)
			BOOK_STRINGTOKEY_CASE(F13)
			BOOK_STRINGTOKEY_CASE(F14)
			BOOK_STRINGTOKEY_CASE(F15)
			{
	"Pause", sf::Keyboard::Pause
	}
	};
}
sf::Keyboard::Key toKey(const std::string key) {
	return utility::keyMap.find(key)->second;
}

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}


unsigned long long hashString(std::string s) {
	unsigned long long hashValue = 0, p = 131313;
	for (int i = 0; i < (int)s.length(); i++) {
		hashValue = hashValue * p + s[i];
		p = p * p;
	}
	return hashValue;
}

bool createDirectory(const std::string& path) {
	int result = _mkdir(path.c_str());
	assert(!result);
	return !result;
}

void	processInputString(std::string& s) {
	s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
}