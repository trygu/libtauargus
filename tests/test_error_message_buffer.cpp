#include "TauArgus.h"
#include "Ghmiter.h"
#include "JJFormat.h"
#include <limits>
#include <string>
int main() {
    TauArgus engine;
    for (long value : {std::numeric_limits<long>::min(), std::numeric_limits<long>::max()}) {
        const std::string text = engine.GetErrorString(value);
        if (text.find(std::to_string(value)) == std::string::npos) return 1;
    }
    CGhmiter importer;
    CTable table;
    long dims[] = {0};
    FILE *empty = tmpfile();
    if (!empty) return 2;
    const bool accepted = importer.SetSecUnSafe(&table, empty, dims, -1, false);
    rewind(empty);
    CJJFormat jj;
    const bool accepted_jj = jj.SetSecUnSafe(&table, nullptr, empty, false);
    fclose(empty);
    if (accepted) return 3;
    if (accepted_jj) return 4;
    return 0;
}
