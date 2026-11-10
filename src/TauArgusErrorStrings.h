/*
* Embedded catalog of the core ErrorCodes (see defines.h).
*
* The legacy GUI loaded TauArgus.properties from the working directory at
* runtime; the headless engine has no reliable working directory, so the
* table is compiled in. The messages are reconstructed from the ErrorCodes
* enum names and their use in TauArgus.cpp (the original .properties file
* does not survive in git history).
*/
#if !defined TauArgusErrorStrings_h
#define TauArgusErrorStrings_h

#include "defines.h"

struct TauErrorEntry {
	long code;
	const char *text;
};

static const TauErrorEntry TauErrorTable[] = {
	{ FILENOTFOUND,                 "File not found" },
	{ CANTOPENFILE,                 "Cannot open file" },
	{ EMPTYFILE,                    "File is empty" },
	{ WRONGLENGTH,                  "Wrong length" },
	{ RECORDTOOSHORT,               "Record too short" },
	{ WRONGRECORD,                  "Wrong record" },
	{ NOVARIABLES,                  "No variables defined" },
	{ NOTABLES,                     "No tables defined" },
	{ NOTENOUGHMEMORY,              "Not enough memory" },
	{ NOTABLEMEMORY,                "Not enough memory for table" },
	{ SUBTABLENOSUB,                "Subtable has no sub codes" },
	{ SUBTABLEWRONGVAR,             "Subtable uses the wrong variable" },
	{ NODATAFILE,                   "Data file not found" },
	{ PROGRAMERROR,                 "Program error" },
	{ WRONGHIERARCHY,               "Wrong hierarchy" },
	{ TABLENOTSET,                  "Table is not set" },
	{ VARIABLENOTSET,               "Variable is not set" },
	{ CODENOTINCODELIST,            "Code not in code list" },
	{ ISNOTNUMERIC,                 "Value is not numeric" },
	{ FREQPERCOUTOFRANGE,           "Frequency percentage out of range" },
	{ STATUSPERCOUTOFRANGE,         "Status percentage out of range" },
	{ PROBLEMSREADINGFREEFORMAT,    "Problems reading free format file" },
	{ CELLALREADYFILLED,            "Cell already filled" },
	{ CANNOTFILLTABLE,              "Cannot fill table" },
	{ TABLENOTADDITIVE,             "Table is not additive" },
	{ CANNOTMAKETOTALS,             "Cannot calculate totals" },
	{ CANNOTCALCULATESAFETY,        "Cannot calculate safety" },
	{ CODEDOESNOTEXIST,             "Code does not exist" },
	{ HC_FILENOTFOUND,              "Hierarchy file not found" },
	{ HC_LEVELSTRINGEMPTY,          "Hierarchy level string is empty" },
	{ HC_CODEISMISSING,             "Hierarchy code is missing" },
	{ HC_LEVELINCORRECT,            "Hierarchy level is incorrect" },
	{ HC_CODEEMPTY,                 "Hierarchy code is empty" },
	{ HC_NOTHIERARCHICAL,           "Variable is not hierarchical" },
	{ HC_HASSPLITDIGITS,            "Hierarchy code has split digits" },
	{ HC_CODETOOLONG,               "Hierarchy code is too long" },
	{ E_HARD,                       "Recode: hard error" },
	{ E_SOFT,                       "Recode: soft error" },
	{ E_NOVARTABDATA,               "Recode: no variable or table data" },
	{ E_LENGTHWRONG,                "Recode: wrong length" },
	{ E_RANGEWRONG,                 "Recode: wrong range" },
	{ E_VARINDEXWRONG,              "Recode: wrong variable index" },
	{ E_EMPTYSPEC,                  "Recode: empty specification" },
	{ R_FROMTOOBIG,                 "Recode: FROM value too big" },
	{ R_CODENOTINLIST,              "Recode: code not in list" },
	{ R_NOSENSE,                    "Recode: no sense" },
	{ R_MISSING2VALID,              "Recode: missing to valid value" },
	{ GHM_TABLEINDEXWRONG,          "Ghmiter: wrong table index" },
	{ GHM_NOTPREPARED,              "Ghmiter: not prepared" },
	{ GHM_CODEWIDTHTOOBIG,          "Ghmiter: code width too big" },
	{ GHM_TABELLEINCORRECT,         "Ghmiter: table incorrect" },
	{ GHM_STEUERINCORRECT,          "Ghmiter: steering data incorrect" },
	{ GHM_EINGABEINCORRECT,         "Ghmiter: input incorrect" },
	{ GHM_EXECUTEINCORRECT,         "Ghmiter: execute incorrect" },
	{ GHM_SOURCECELLINCORRECT,      "Ghmiter: source cell incorrect" },
	{ GHM_NOFILEAUSGABE,            "Ghmiter: no output file" },
	{ JFF_NOFILE,                   "JJFormat: file not found" },
	{ JJF_SOURCECELLINCORRECT,      "JJFormat: source cell incorrect" },
	{ JJF_TABLEINDEXWRONG,          "JJFormat: wrong table index" },
	{ NOTABLE,                      "AMPL: no table" },
	{ TABLEWITHMORETHAN2VARIABLES,  "AMPL: table has more than two variables" },
	{ FIRSTVARNOTHIERARCHICAL,      "AMPL: first variable not hierarchical" },
	{ SECONDVARNOTFLAT,             "AMPL: second variable not flat" },
	{ NOMEMORYFORSUBCODES,          "AMPL: no memory for sub codes" },
	{ COULDNOTCREATESUBCODES,       "AMPL: could not create sub codes" },
	{ COULDNOTOPENFILE,             "AMPL: could not open file" },
	{ COULDNOTCREATEAMPL,           "AMPL: could not create AMPL file" }
};

static inline const char *TauErrorString(long code)
{
	size_t n = sizeof(TauErrorTable) / sizeof(TauErrorTable[0]);
	for (size_t i = 0; i < n; i++) {
		if (TauErrorTable[i].code == code) {
			return TauErrorTable[i].text;
		}
	}
	return 0;
}

#endif // TauArgusErrorStrings_h
