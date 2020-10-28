#include <ostream>
namespace Color {
    enum ColorNum {
        DEFAULT = 39,
		RED = 31, 
		GREEN = 32,
		BLUE = 34, 
		MAGENTA = 35, 
		CYAN = 36, 
		LIGHT_GRAY = 37
    };
    std::ostream& operator<<(std::ostream& os, ColorNum color) {
        return os << "\033[" << static_cast<int>(color) << "m";
    }
}