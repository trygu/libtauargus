#include "TauArgus.h"

#include <iostream>
#include <stdexcept>

static void require(bool condition, const char *message)
{
    if (!condition) throw std::runtime_error(message);
}

// MaximumProtectionLevel and GetMinimumCellValue must treat a bad or
// unset table index as "no table" (defined zero result), not as an
// out-of-bounds dereference. GetTotalTabelSize already does; this is
// the regression guard for the two getters that did not.
static void require_unavailable(TauArgus &engine, long index,
                                const char *message)
{
    require(engine.MaximumProtectionLevel(index) == 0.0, message);
    double minimum = -1.0, maximum = -1.0;
    require(!engine.GetMinimumCellValue(index, &minimum, &maximum), message);
    require(minimum == 0.0 && maximum == 0.0, message);
    long cells = -1, size = -1;
    require(!engine.GetTotalTabelSize(index, &cells, &size), message);
    require(cells == 0 && size == 0, message);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    try {
        {
            TauArgus engine;
            require_unavailable(engine, 0, "Unconfigured table 0 accepted");
            require_unavailable(engine, -1, "Negative table index accepted");
            require_unavailable(engine, 999, "Out-of-range table index accepted");
        }
        {
            TauArgus engine;
            require(engine.SetNumberVar(1), "SetNumberVar failed");
            require(engine.SetNumberTab(1), "SetNumberTab failed");
            require_unavailable(engine, 1, "Index beyond m_ntab accepted");
            require_unavailable(engine, 999, "Large index beyond m_ntab accepted");
        }
        std::cout << "Table index guard checks passed\n";
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
