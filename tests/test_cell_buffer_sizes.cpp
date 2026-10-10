#include "TauArgus.h"

#include <iostream>
#include <stdexcept>

static void require(bool condition, const char *message)
{
    if (!condition) throw std::runtime_error(message);
}

static void require_unavailable(TauArgus &engine, long index,
                                const char *message)
{
    long dimensions = -1, cell_scores = -1, holding_scores = -1;
    require(!engine.GetTableCellBufferSizes(index, &dimensions, &cell_scores,
                                           &holding_scores), message);
    require(dimensions == -1 && cell_scores == -1 && holding_scores == -1,
            "Rejected queries must not overwrite output capacities");
}

int main(int argc, char **argv)
{
    try {
        require(argc == 2, "Pass the microdata fixture path");
        TauArgus engine;
        require(engine.SetNumberVar(2), "SetNumberVar failed");
        require(engine.SetNumberTab(1), "SetNumberTab failed");
        require_unavailable(engine, 0, "Unexplored table reported capacities");
        require(engine.SetVariable(0, 1, 1, 0, 1, "-", "", "T", false,
                                   "", "", true, false, false, false, false,
                                   false), "Categorical SetVariable failed");
        require(engine.SetVariable(1, 2, 3, 0, 0, "", "", "", false,
                                   "", "", false, true, false, false, false,
                                   false), "Response SetVariable failed");
        engine.SetInFileInfo(true, "");
        long error = 0, line = 0, variable = 0;
        require(engine.ExploreFile(argv[1], &error, &line, &variable),
                "ExploreFile failed");
        require_unavailable(engine, 0, "Unconfigured table reported capacities");
        long explanatory[] = {0};
        require(engine.SetTable(0, 1, explanatory, false, 1, 1, -1, -1,
                                "N", 1, 1.0, 1.0, -1, false), "SetTable failed");
        require_unavailable(engine, 0, "Unprepared table reported capacities");
        require_unavailable(engine, -1, "Negative table index was accepted");
        require_unavailable(engine, 1, "Out-of-range table index was accepted");
        long table = 0;
        require(engine.ComputeTables(&error, &table), "ComputeTables failed");
        long dimensions = -1, cell_scores = -1, holding_scores = -1;
        require(engine.GetTableCellBufferSizes(0, &dimensions, &cell_scores,
                                              &holding_scores),
                "Prepared table did not report capacities");
        require(dimensions == 1 && cell_scores == 0 && holding_scores == 0,
                "Prepared table without score rules returned wrong capacities");
        long recode_error = 0, recode_line = 0, recode_position = 0;
        const char *warning = nullptr;
        require(engine.DoRecode(0, "C: A,B", 1, "-", "", &recode_error,
                                &recode_line, &recode_position, &warning),
                "DoRecode failed");
        engine.ApplyRecode();
        require(engine.GetTableCellBufferSizes(0, &dimensions, &cell_scores,
                                              &holding_scores),
                "Prepared recoded table did not report capacities");
        require(dimensions == 1 && cell_scores == 0 && holding_scores == 0,
                "Prepared recoded table returned wrong capacities");
        std::cout << "Table preparation and buffer capacity checks passed\n";
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
