/*#if !defined(AFX_TABLE_H__6CE83D0A_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_)
#define AFX_TABLE_H__6CE83D0A_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000*/
#if !defined Table_h
#define Table_h

#include "defines.h"
#include "datacell.h"
#include "variable.h"

// Table.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTable window

class CTable
{
// Construction
public:
	CTable();

// Attributes
public:
	long NumberofMaxScoreCell; //Saves the number of MaxScore to be stored per cell--Cell Level
	long NumberofMaxScoreHolding; //Saves the number of MaxScore to be stored per cell--Holding Level
	bool Prepared;         // if table is already prepared
	long nDim;              // number of variables (= dimensions) in table
   int  SizeDim[MAXDIM];   // = nCode of corresponding variable

	int ExplVarnr[MAXDIM];  // index of each explanatory variable
	int ResponseVarnr;      // index of respons variable
	int ShadowVarnr;        // index of shadow variable
	int CostVarnr;          // index of cost variable; or CVT_FREQ etc, these values are always < 0
	int PeepVarnr;

	// Transformation the Cost function.
	double Lambda;
	double MaxScaledCost;
	double MinLPL;          // Minimum protection level avoiding problems when writing intermediate files  

	bool SetMissingAsSafe;

	// Add
//	int SafetyRule;         // DOMINANCE or PQRULE or None

//	bool TwoRulesForCell;
//	bool TwoRulesForHolding;
	// for dominance safety method
	bool DominanceRule;
	int DominanceNumberCell_1;
	int DominancePercCell_1;
	int DominanceNumberCell_2;
	int DominancePercCell_2;

	int DominanceNumberHolding_1;
	int DominancePercHolding_1;
	int DominanceNumberHolding_2;
	int DominancePercHolding_2;
	// for PriorPosterial safety method or PQ-Rule
	bool PQRule;
	int PQ_PCell_1;
	int PQ_QCell_1;
	int PQ_NCell_1;
	int PQ_PCell_2;
	int PQ_QCell_2;
	int PQ_NCell_2;

	int PQ_PHolding_1;
	int PQ_QHolding_1;
	int PQ_NHolding_1;
	int PQ_PHolding_2;
	int PQ_QHolding_2;
	int PQ_NHolding_2;

	// for Peep regel
	long PeepPercCell_1;
	long PeepPercCell_2;

	long PeepPercHolding_1;
	long PeepPercHolding_2;

	long PeepSafetyRangePercCell;
	long PeepSafetyRangePercHolding;

	//
	long PeepMinFreqCell;
	long PeepMinFreqHold;


	int SafeMinRec; //Minimaal aantal bijdragers
	int SafeMinHoldings; // minimum aantal holdings
/// Safety Margins

	long CellFreqSafetyPerc;
	long HoldingFreqSafetyPerc;
	long ManualSafetyPerc;
	long NSEmptySafetyRange;
	long SingletonSafetyRangePerc;
	double ZeroSafetyRange;

//	CDataCell *Cell;          // counting space
	CPtrArray CellPtr;
	long nCell;               // number of cells
	//int nMaxCellValues;


// About the Table
	bool IsFrequencyTable;
	bool ApplyHolding;
	BOOL ApplyWeight;
	BOOL ApplyWeightOnSafetyRule;
	BOOL ApplyPeeper;
	BOOL ApplyZeroRule;
	BOOL EmptyCellsAsNSEmpty;
	int HasRecode;


	// Operations

	// have to make the operator =
	// since it does not work with CPtrArray
	void operator = (CTable & table2);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTable)
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitializeHoldingNrs();
	long GetCellNrFromIndices(long *Indices);
	BOOL GetCellDistance(long CellNr, long *Dist);
	BOOL IsCellSafe(long c);
	BOOL IsCellUnsafe(long c);
	int * CellDistance;
	BOOL PrepareComputeDistance();
	int  GetCellDistance(long *dim1, long *dim2);
	void GetStatusStatistics(long *Freq,long *CellFreq, long *HoldingFreq, double *CellResp, double *CellCost);
	void SetCellSecondaryUnsafe(long *dims);
	void SetSecondary(CVariable *var, long *dims, long *CellDims, int niv, long *nSetSecondary);
	BOOL SetSecondaryHITAS(FILE *fd, CVariable *var, long *nSetSecondary);
	CDataCell * GetCell(long *VarValueList);
	CDataCell * GetCell(long CellNr);
	void GetStatusAndCostPerDim(long *Status, double *Cost);
	void UndoSecondarySuppress(long SortSuppress);
	BOOL GetIndicesFromCellNr(long CellNr, long* Indices);
	BOOL CleanUp();
	int  ComputeCellSafeCode(CDataCell &dc);
	BOOL PrepareTable();
	BOOL UnsafeCellDominance(CDataCell &dc);
	BOOL UnsafeCellPQRule(CDataCell &dc);
	BOOL UnsafeCellMinRec(CDataCell& dc);
	BOOL UnsafeCellPeep(CDataCell &dc);
	void CountUnSafe(long *DimList, int FixedDimNr, long *Unsafe, int niv);

	BOOL GetUnsafeCells(int VarIndex, int VarCodeIndex, long *nUnsafe);
	BOOL GetUnsafeCells(int VarIndex, long *nUnsafe);
	//BOOL GetCell(long *VarValueList, CDataCell& datacell);
	//BOOL GetCell(long CellNr, CDataCell& datacell);
	long GetMemSizeTable();
	long GetSizeTable();

	BOOL SetCell(long *VarValueList, CDataCell& datacell);
	BOOL SetCell(long CellNr, CDataCell& datacell);
	BOOL SetDimSize(int dim, int value);
//  BOOL SetDominance(long DominanceNumber, long DominancePerc);


	BOOL SetDominance(long *DominanceNumber, long *DominancePerc);
	//BOOL SetPQRule(long PriorPosteriorP, long PriorPosteriorQ, long PriorPosteriorN);
	BOOL SetPQRule(long *PriorPosteriorP,long *PriorPosteriorQ, long *PriorPosteriorN);
	BOOL SetSafeMinRecAndHold(long SafeMinRec, long SafeMinholdings);
	BOOL SetVariables(int inDim, long* ExplVar, long RespVar, long ShadVar, long CostVar, long PeepVar);
	BOOL SetExplVariables(int nDim, long* ExplVar);
	BOOL SetProtectionLevelCell(CDataCell &datacell);
	BOOL SetProtectionLevelCellFrequency(CDataCell &datacell, long Base, long K);
	virtual ~CTable();
protected:
	//{{AFX_MSG(CTable)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
/*
	DECLARE_MESSAGE_MAP()
*/
};
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_TABLE_H__6CE83D0A_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_)
