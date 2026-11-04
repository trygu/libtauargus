#include "TauArgus.h"
#include <limits>
#include <string>
int main() {
    TauArgus engine;
    for (long value : {std::numeric_limits<long>::min(), std::numeric_limits<long>::max()}) {
        const std::string text = engine.GetErrorString(value);
        if (text.find(std::to_string(value)) == std::string::npos) return 1;
    }
    return 0;
}
