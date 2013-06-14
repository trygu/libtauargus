/*#if !defined(AFX_VARIABLE_H__6CE83D09_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_)
#define AFX_VARIABLE_H__6CE83D09_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/
#if !defined Variable_h
#define Variable_h
#include "defines.h"
#include "code.h"
#include "SubCodeList.h"

typedef struct {
	CStringArray sCode;			// list of codes generated from recode, sorted upwards
	int nCode;              // number of codes, should be equal to sCode.GetSize()
	CString Missing1;       // first missing value
	CString Missing2;       // second missing value
	int nMissing;	          // number of missing codes (usually 1 or 2)
	int *DestCode;          // m_var[SrcVar].nCode times an index to sCode
	int CodeWidth;          // max length sCodes
	int nBogus;
	CCode *hCode;           // Properties hierarchical codes

} RECODE;


// Variable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVariable window

class CVariable
{
// Construction
public:
	CVariable();

// Attributes
public:
	long bPos;              // starting position in record (first byte 0)
	long nPos;              // number of bytes
	long nDec;              // number of decimals

	bool IsPeeper;					//variable is Pieper
	bool IsCategorical;			// variable is categorical (sex, regio)
	bool IsNumeric;		      // variable is counting item (income, number of persons)
	bool IsWeight;		    	// variable is weight
	bool IsHierarchical;   	// variable is hierarchical
	bool IsHolding;       	// variable is holding indicator

	int nMissing;	          // number of missing codes (usually 1 or 2)
	CString Missing1;       // first missing value
	CString Missing2;       // second missing value
	CString TotalCode;      // code for Total

  // computed during ExploreFile
	double MinValue;        // For numeric variables : minimum in data file
	double MaxValue;        //                         maximum in data file


	CStringArray sCode;			// For categorical variables: list of codes generated from microfile or from a file
	CByteArray hLevel;      // Levels hierarchical codelist, nCodes long
	CByteArray hLevelBasic; // Basic code hierarchical codelist, nCodes long

	int nCode;              // number of codes, should be equal to sCode.GetSize()

	// only relevant if IsHierarchical
	int nDigitSplit;                // number of digit groups (only if hierarchical)
	int DigitSplit[MAXDIGITGROUP];  // Digit groups
	CCode *hCode;                   // Properties hierarchical codes

	long TableIndex;        // used in FillTables
	int  ValueToggle;       // used in FillTables
	double Value;           // used in FillTables
	bool HasRecode;        // toggle for Recode specification
	bool HasCodeList;       // toggle for Codelist specification form file
	RECODE Recode;          // recode specification, only relevant if HasRecode = true
	CString PeepCode1;
	CString PeepCode2;

	bool PositionSet;
	long NumSubCodes;
	CSubCodeList *m_SubCodes;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariable)
	//}}AFX_VIRTUAL

// Implementation
public:
	int nBogus;
	int  hfCodeWidth; // max width code hierarchical codelist from file
	void UndoRecode();
	CCode* GethCode();
	bool SetHierarchicalRecode();
	void PrintLevelStrings(FILE *fd, int nLevel, LPCTSTR LevelString);
	void PrintLevelCode(FILE *fd, LPCTSTR code, LPCTSTR LevelString);
	void WriteBogusCodelist(FILE *fd, LPCTSTR LevelString, int index, int level, int boguslevel, int ncode, CStringArray *CodeList);
	bool WriteCodelist(LPCTSTR FileName, LPCTSTR LevelString, LPCTSTR Name, bool bogus);
	bool SetHierarchicalDigits(long nDigitPairs, long *nDigits);
	int  FindHierarchicalCode(LPCTSTR code);
	int  FindAllHierarchicalCode(LPCTSTR code);
	int  SetCodeList(LPCTSTR FileName, LPCTSTR LevelString);
	void SetActive(long CodeIndex, bool active);
	bool SetHierarch();
	void GetGHMITERCode(int i, char* code);
	int  GetCodeWidth();
	bool IsCodeBasic(int i);
	CStringArray * GetCodeList();
	int  GetnMissing();
	CString GetCode(int i);
	int GetLevel(int i);
	long GetDepthOfHerarchicalBoom();
	int  GetnCode();
	int  GetnBogus();
	int  GetnCodeActive();
	int  GetnCodeInActive();
	bool AddCode(const char *newcode, bool tail);
	bool ComputeHierarchicalCodes();
	bool SetMissing(LPCTSTR Missing1, LPCTSTR Missing2, long NumMissing);
	bool SetTotalCode(LPCTSTR sTotalCode);
	bool SetType(bool IsCategorical, bool IsNumeric, bool IsWeight, bool IsHierarchical, bool IsHolding, bool IsPeeper);
	bool SetPeepCodes(CString Peep1, CString Peep2);
	bool SetPosition(long bPos, long nPos, long nDec);
	bool SetDecPosition(long lnDec);
	int  BinSearchStringArray(CStringArray &s, CString x, int nMissing, bool &IsMissing);
	virtual ~CVariable();
	long OrganizeCodelist();
	long NumberOfSubCodeList();
	bool PrepareSubCodeList();
	bool CreateSubCodeForHierarchicalCode(long CodeIndex, long SubCodeSequenceNumber);
	bool CreateSubCodeForNonHierarchicalCode();
	bool FillSubCodeList();
	long FindNumberOfChildren(long CodeIndex);
	bool FindChildren(long NumChild, CStringArray &Child, long CodeIndex, long *Index);


	// Generated message map functions

protected:
	//{{AFX_MSG(CVariable)
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

//#endif // !defined(AFX_VARIABLE_H__6CE83D09_63CC_11D5_BC56_00C04F9A7DB5__INCLUDED_)
