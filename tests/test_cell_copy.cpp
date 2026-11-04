#include "DataCell.h"

int main() {
    CDataCell original(2, 2, 1, 1);
    original.SetResp(42);
    original.MaxScoreCell[0] = 7;
    original.MaxScoreWeightCell[0] = 8;
    original.MaxScoreHolding[0] = 9;
    original.MaxScoreWeightHolding[0] = 10;
    original.HoldingnrPerMaxScore[0] = 11;
    CDataCell copy(original);
    if (copy.GetResp() != 42 || copy.MaxScoreCell[0] != 7 ||
        copy.MaxScoreWeightCell[0] != 8 || copy.MaxScoreHolding[0] != 9 ||
        copy.MaxScoreWeightHolding[0] != 10 || copy.HoldingnrPerMaxScore[0] != 11) return 1;
    copy.MaxScoreCell[0] = 99;
    if (original.MaxScoreCell[0] != 7) return 2;
    CDataCell assigned(1, 0, 0, 0);
    assigned = original;
    assigned.MaxScoreHolding[0] = 98;
    if (original.MaxScoreHolding[0] != 9 || assigned.GetResp() != 42) return 3;
    original = original;
    if (original.MaxScoreCell[0] != 7 || original.GetResp() != 42) return 4;
    CDataCell empty;
    assigned = empty;
    if (assigned.MaxScoreCell || assigned.MaxScoreWeightCell || assigned.MaxScoreHolding ||
        assigned.MaxScoreWeightHolding || assigned.HoldingnrPerMaxScore) return 5;
    return 0;
}
