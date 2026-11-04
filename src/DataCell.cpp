/*
* Argus Open Source
* Software to apply Statistical Disclosure Control techniques
* 
* Copyright 2014 Statistics Netherlands
* 
* This program is free software; you can redistribute it and/or 
* modify it under the terms of the European Union Public Licence 
* (EUPL) version 1.1, as published by the European Commission.
* 
* You can find the text of the EUPL v1.1 on
* https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
* 
* This software is distributed on an "AS IS" basis without 
* warranties or conditions of any kind, either express or implied.
*/

#include <cstring>
#include <cmath>
#include <algorithm>
#include <memory>

#include "General.h"
#include "DataCell.h"

namespace {
template <typename T>
std::unique_ptr<T[]> copy_scores(const T *source, int count)
{
    if (!source || count <= 0) return std::unique_ptr<T[]>();
    std::unique_ptr<T[]> result(new T[count]);
    std::copy_n(source, count, result.get());
    return result;
}
}

CDataCell::CDataCell(const CDataCell& other) : CDataCell()
{
    *this = other;
}

CDataCell& CDataCell::operator=(const CDataCell& other)
{
    if (this == &other) return *this;
    // Allocate all owned arrays before changing the destination.
    auto cell = copy_scores(other.MaxScoreCell, other.nMaxScoreCell);
    auto cell_weight = copy_scores(other.MaxScoreWeightCell, other.nMaxScoreCell);
    auto holding = copy_scores(other.MaxScoreHolding, other.nMaxScoreHolding);
    auto holding_weight = copy_scores(other.MaxScoreWeightHolding, other.nMaxScoreHolding);
    auto holding_number = copy_scores(other.HoldingnrPerMaxScore, other.nMaxScoreHolding);
    Resp = other.Resp;
    NWResp = other.NWResp;
    Cost = other.Cost;
    Shadow = other.Shadow;
    CellKey = other.CellKey;
    CellKeyNoZeros = other.CellKeyNoZeros;
    Freq = other.Freq;
    Weight = other.Weight;
    FreqHolding = other.FreqHolding;
    RoundedResp = other.RoundedResp;
    CTAValue = other.CTAValue;
    CKMValue = other.CKMValue;
    Status = other.Status;
    TempShadow = other.TempShadow;
    HoldingNr = other.HoldingNr;
    PeepSortCell = other.PeepSortCell;
    PeepSortHolding = other.PeepSortHolding;
    TempPeepSort = other.TempPeepSort;
    PeepCell = other.PeepCell;
    PeepHolding = other.PeepHolding;
    RealizedUpperValue = other.RealizedUpperValue;
    RealizedLowerValue = other.RealizedLowerValue;
    LowerProtectionLevel = other.LowerProtectionLevel;
    UpperProtectionLevel = other.UpperProtectionLevel;
    MinScoreCell = other.MinScoreCell;
    MinScoreWeightCell = other.MinScoreWeightCell;
    nMaxScoreCell = other.nMaxScoreCell;
    nMaxScoreHolding = other.nMaxScoreHolding;
    IsFilled = other.IsFilled;
    delete [] MaxScoreCell;
    delete [] MaxScoreWeightCell;
    delete [] MaxScoreHolding;
    delete [] MaxScoreWeightHolding;
    delete [] HoldingnrPerMaxScore;
    MaxScoreCell = cell.release();
    MaxScoreWeightCell = cell_weight.release();
    MaxScoreHolding = holding.release();
    MaxScoreWeightHolding = holding_weight.release();
    HoldingnrPerMaxScore = holding_number.release();
    return *this;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BIGNUMBER 1.0E16

/////////////////////////////////////////////////////////////////////////////
// CDataCell
// Constructor used in principle for creating a new cell that is added to the table
CDataCell::CDataCell(int NumberMaxScoreCell, int NumberMaxScoreHolding, int IsHolding, int IsWeight)
{
//	FILE *fd;
//	fd = fopen("E:/Temp/Debug.txt","a");
//		fprintf(fd,"%Xh%s\n", this,"		CDatacell		Const		()  ");
//	fclose(fd);
	Resp = 0;
    NWResp = 0;
	Cost = 0;
	Shadow = 0;
    CellKey = 0;
    CellKeyNoZeros = 0;
	Freq = 0;
	Weight = 0;
	FreqHolding = 0;
	RoundedResp = 0;
    CTAValue = 0;
    CKMValue = 0;
    // Needed for CKMType = "D"
    // Set to large double 
    MinScoreCell = BIGNUMBER;
    MinScoreWeightCell = 0;        

	Status = CS_EMPTY;
	TempShadow = 0;
    HoldingNr = IsHolding ? WITH_HOLDING : WITHOUT_HOLDING;
	PeepSortCell = EMPTY;
	PeepSortHolding = EMPTY;
	TempPeepSort = EMPTY;

	PeepCell = 0;
	PeepHolding = 0;

  //set ini values for realized upper and lower.as 0
	RealizedUpperValue = 0;
	RealizedLowerValue = 0;
	LowerProtectionLevel = 0;
	UpperProtectionLevel = 0;
        
    MaxScoreCell = 0; //initialize to NULL
    MaxScoreWeightCell = 0; //initialize to NULL
    MaxScoreHolding = 0; //initialize to NULL
    MaxScoreWeightHolding = 0; //initialize to NULL
    HoldingnrPerMaxScore = 0; //initialize to NULL

	nMaxScoreCell = NumberMaxScoreCell;
	if (nMaxScoreCell > 0){
        // allocate memory for MaxScore and MaxScoreWeight
        // and fill with values 0.0
        MaxScoreCell = new double[nMaxScoreCell];
        memset(MaxScoreCell, 0, sizeof(double) * nMaxScoreCell);

		if (IsWeight){
			MaxScoreWeightCell = new double[nMaxScoreCell];
			memset(MaxScoreWeightCell, 0, sizeof(double) * nMaxScoreCell);
        }
	}

	nMaxScoreHolding = NumberMaxScoreHolding;
	if (IsHolding && nMaxScoreHolding > 0){
        // allocate memory for MaxScore and MaxScoreWeight
        MaxScoreHolding = new double[nMaxScoreHolding];
        memset( MaxScoreHolding, 0, sizeof(double) * nMaxScoreHolding);
            
        if (IsWeight){
			MaxScoreWeightHolding = new double[nMaxScoreHolding];
			memset( MaxScoreWeightHolding, 0, sizeof(double) * nMaxScoreHolding);
        }
            
        // Allocate Memory for HoldingnrMaxScore
        HoldingnrPerMaxScore = new int[nMaxScoreHolding];
        memset( HoldingnrPerMaxScore, -1, sizeof(int) * nMaxScoreHolding);
	}

	IsFilled = false;
}

// constructor used within functions. does not have the arrays for
// maxscore
CDataCell::CDataCell()
{
//	FILE *fd;
//	fd = fopen("E:/Temp/Debug.txt","a");
//	fprintf(fd,"%Xh%s\n", this,"		CDatacell		Const		()  ");
//	fclose(fd);
	Resp = 0;
    NWResp = 0;
	Cost = 0;
	Shadow = 0;
    CellKey = 0;
    CellKeyNoZeros = 0;
	Freq = 0;
	Weight = 0;
	FreqHolding = 0;
	RoundedResp = 0;
	CTAValue = 0;
    CKMValue = 0;

	Status = CS_EMPTY;
	TempShadow = 0;
	HoldingNr = WITHOUT_HOLDING;
	PeepSortCell = EMPTY;
	PeepSortHolding = EMPTY;
	TempPeepSort = EMPTY;

	PeepCell = 0;
	PeepHolding = 0;

  //set ini values for realized upper and lower.as 0
	RealizedUpperValue = 0;
	RealizedLowerValue = 0;
	LowerProtectionLevel = 0;
	UpperProtectionLevel = 0;
        
    // Needed for CKMType = "D"
    // Set to large double 
    MinScoreCell = BIGNUMBER;
    MinScoreWeightCell = 0;

	nMaxScoreCell = 0;
	MaxScoreCell = 0;
	MaxScoreWeightCell = 0;
	nMaxScoreHolding = 0;
	MaxScoreHolding = 0;
	MaxScoreWeightHolding = 0;
	HoldingnrPerMaxScore = 0;
	IsFilled = false;
}

// Destructor. All arrays that are created should be cleaned.
CDataCell::~CDataCell()
{
//	FILE *fd;
//	fd = fopen("E:/Temp/Debug.txt","a");
//	fprintf(fd,"%Xh%s\n", this,"		CDatacell		Dest  ");
//	fclose(fd);

	delete [] MaxScoreCell;
	delete [] MaxScoreWeightCell;
	
	delete [] MaxScoreHolding;
	delete [] MaxScoreWeightHolding;
	delete [] HoldingnrPerMaxScore;
}

// merges the max score holding from two cells along with the holding numbers.
// this is used in recoded tables.
void CDataCell::MergeScoreHolding(double *a, int *ah, double *b, int *bh, int n)
{
    int i,j,ai = 0;
	
    if  (b == 0) return;
    double  *tempbval = new double [n] ;
    int     *tempbhol = new int [n];

    for (i= 0; i< n; i++){
        tempbval[i] = b[i];
		tempbhol[i] = bh[i];
    }

    // add holdings that are equal with b and put a[i] in the temp
    for (i=0; i<n; i ++){
		for (j= 0; j<n; j++){
			if ((ah[i] == tempbhol[j])){
				a[i] = a[i] + tempbval[j];
				tempbval[j] = a[i] + tempbval[j];
			}
		}
    }
	
    for (i = 0; i < n; i++){
		if (tempbval[i] > a[ai]){
			// shift down
			for (j = n - 2; j >= ai; j--){
				a[j + 1] = a[j];
				ah[j + 1] = ah[j];
			}
			a[ai] = tempbval[i];
			ah[ai] = tempbhol[i];
		} 
		else{
            ai++;
            i--;
		}
		if (ai == n) break; // all elements from b smaller than a
    }
    delete [] tempbval;
    delete [] tempbhol;
}

// merges two arrays when cells are merged. This is used in recoded tables
void CDataCell::MergeScore(double *a, double *aw, double* b, double *bw, int n)  // for MaxScore and MaxScoreWeight
{ 
    int i, j, ai = 0;

    if (b == 0) return; // no scores

    for (i = 0; i < n; i++){
		if (b[i] > a[ai]){
        // shift down
            for (j = n - 2; j >= ai; j--){
				a[j + 1] = a[j];
				if (aw != 0){
                    aw[j + 1] = aw[j];
				}
            }
            a[ai] = b[i];
            if ((aw != 0) && (bw != 0 )){
				aw[ai++] = bw[i];
            }
		} 
		else{
            ai++;
            i--;
		}
		if (ai == n) break; // all elements from b smaller than a
    }
}

// Note the two functions below could be combined and made into one function with a boolean
// to direct you to use weight or not
// Gets the dominance Perc of cell.
double CDataCell::GetDominancePercCell(bool ApplyWeight, bool ApplyWeightOnSafetyRule, long DominanceNumber)
{ 
	ASSERT(MaxScoreCell != 0);
	if (MaxScoreCell[0] == 0) return 0;
	if (Shadow == 0) return 0;

	return ComputeWeightedScoreCell(ApplyWeight && ApplyWeightOnSafetyRule,DominanceNumber ) * 100.0 / Shadow;
}

// Gets the dominance Perc of holding. These two 
double CDataCell::GetDominancePercHolding(bool ApplyWeight, bool ApplyWeightOnSafetyRule, long DominanceNumber)
{ 
	ASSERT(MaxScoreHolding != 0);
	if (MaxScoreHolding[0] == 0) return 0;
	if (Shadow == 0) return 0;

	return ComputeWeightedScoreHolding(ApplyWeight && ApplyWeightOnSafetyRule,DominanceNumber ) * 100.0 / Shadow;
}

// Gets PQ for cell.

double CDataCell::GetPQCell(double p, double q, long n, bool ApplyWeight, bool ApplyWeightOnSafetyRule)
{
	if (!ApplyWeight || !ApplyWeightOnSafetyRule) {  
		int i;
		double s = 0;
		for (i = 0; i <= n; i++) {
			s += MaxScoreCell[i];
		}
		return (p / 100) * MaxScoreCell[0] + (q / 100) * (s - Shadow);
	}

	// Apply weight // Is this correct?
	return (p / 100) * MaxScoreCell[0] + (q / 100) * (ComputeWeightedScoreCell(true,n+1) - Shadow);
}

//  gets PQ holding
double CDataCell::GetPQHolding(double p, double q, long n, bool ApplyWeight, bool ApplyWeightOnSafetyRule)
{
	if (!ApplyWeight || !ApplyWeightOnSafetyRule) {  
		int i;
		double s = 0;
		for (i = 0; i <= n; i++) {
			s += MaxScoreHolding[i];
		}
		return (p / 100) * MaxScoreHolding[0] + (q / 100) * (s - Shadow);
	}

	// Apply weight
	return (p / 100) * MaxScoreHolding[0] + (q / 100) * (ComputeWeightedScoreHolding(true,n+1) - Shadow);
}

// Each of the top n is factored with the corresponding weights.
double CDataCell::ComputeWeightedScoreCell(bool DoWeight, long NumberOfScores )
{ 
	int i;
	double score = 0;

	if (DoWeight) {
		double WeightScore = 0;
		for (i = 0; i < NumberOfScores; i++) { 
			if (WeightScore + MaxScoreWeightCell[i] < NumberOfScores) {
				score += MaxScoreCell[i] * MaxScoreWeightCell[i];
				WeightScore += MaxScoreWeightCell[i];
			} 
			else {
				score += MaxScoreCell[i] * (NumberOfScores - WeightScore); // remaining part
				break;
			}
		}
		return score;
	}

	// no weight
	for (i = 0; i < NumberOfScores; i++) { 
  		score += MaxScoreCell[i];
	}
	return score;
}

// each of the top n holdings is factored with holdings.
double CDataCell::ComputeWeightedScoreHolding(bool DoWeight, long NumberOfScores )
{ 
	int i;
	double score = 0;

	if (DoWeight) {
		double WeightScore = 0;
		for (i = 0; i < NumberOfScores; i++) { 
			if (WeightScore + MaxScoreWeightHolding[i] < NumberOfScores) {
				score += MaxScoreHolding[i] * MaxScoreWeightHolding[i];
				WeightScore += MaxScoreWeightHolding[i];
			} 
			else {
				score += MaxScoreHolding[i] * (NumberOfScores - WeightScore); // remaining part
				break;
			}
		}
		return score;
	}

	// no weight
	for (i = 0; i < NumberOfScores; i++) { 
  		score += MaxScoreHolding[i];
	}
	return score;
}

// compare two cells. comparison bases is frequency, shadow, response and cost.
// returns true if the two cells are equal and false if not.
bool CDataCell::Compare(const CDataCell &a) const
{
	return Freq == a.Freq
                && DBL_EQ(Resp, a.Resp) 
                && DBL_EQ(Shadow, a.Shadow)
                && DBL_EQ(Cost, a.Cost);
}

/*double CDataCell::GetCost(double Lambda)
{
	if (Lambda > 0)	{
		return pow(Cost, Lambda);
	}
	else
	{
		return log(Cost + 1);
	}
}*/

void CDataCell::Write(){
    printf("NumberofMaxScoreCell = %d\n",nMaxScoreCell);
    for (int i=0;i<nMaxScoreCell;i++){
        printf("%7.5lf, ",MaxScoreCell[i]);
    }
}
