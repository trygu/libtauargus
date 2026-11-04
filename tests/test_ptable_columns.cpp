#include <cstdio>
#include <string>
#include <vector>
#include "PTable.h"
#include "PTableCont.h"

int main() {
    const char *frequency = "test-frequency-columns.csv";
    FILE *file = fopen(frequency, "w");
    if (!file) return 1;
    fputs("i;j;p;diff;p_ub\n0;0;0.3;99;0.3\n0;1;0.7;98;1\n1;0;0.4;97;0.4\n1;1;0.6;96;1\n", file);
    fclose(file);
    PTable table;
    const bool frequency_ok = table.ReadFromFreqFile(frequency);
    remove(frequency);
    if (!frequency_ok) return 2;
    const auto rows = table.GetData();
    if (rows.size() != 2 || rows[0].size() != 2 || rows[0][1].j != 1 ||
        rows[0][1].p_ub != 1 || rows[1][0].p_ub != 0.4) return 3;

    const char *continuous = "test-continuous-columns.csv";
    file = fopen(continuous, "w");
    if (!file) return 4;
    fputs("i;j;p;diff;p_ub;type\n0;0;0.3;99;0.3;all\n0;1;0.7;98;1;all\n1;0;0.4;97;0.4;all\n1;1;0.6;96;1;all\n", file);
    fclose(file);
    PTableCont cont;
    const bool continuous_ok = cont.ReadFromFile(continuous);
    remove(continuous);
    if (!continuous_ok) return 5;
    const auto data = cont.GetData("all");
    if (data.size() != 2 || data.at(0).at(1)[0] != 0.7 ||
        data.at(0).at(1)[1] != 1 || data.at(1).at(0)[1] != 0.4) return 6;
    return 0;
}
