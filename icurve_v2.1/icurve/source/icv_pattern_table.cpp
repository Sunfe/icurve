#include <QString>
#include "icv_pattern_table.h"

QString icvCmdTitlePatternTbl[ICV_MAX_TITLE_PATTERN_NUM]=
{
    "(rfc|bcm|api).+(getTxPsd|getSnr|getQln|getHlog|getNoiseMargin|getBitAlloc|getRmcBitAlloc|getAln)\\s+([0-9]+)\\s+([0-1])\\s*.*$",
	"(fast).+(getQln|getHlog|getXlogDs)\\s+[0-9]+\\s+([0-9]+)\\s+([0-1])\\s*.*$"
};

QString icvCmdDataPatternTbl[ICV_MAX_DATA_PATTERN_NUM][2]=
{
    {"rfc getTxPsd"         , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"rfc getSnr"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"rfc getQln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"rfc getHlog"          , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"rfc getNoiseMargin"   , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"rfc getBitAlloc"      , "\\s+\\d{1,5}\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"rfc getRmcBitAlloc"   , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"rfc getAln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    //api
    {"api getTxPsd"         , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getSnr"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getQln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getHlog"          , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getNoiseMargin"   , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getBitAlloc"      , "\\s+\\d{1,5}\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"api getRmcBitAlloc"   , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    // api getAln:  "0 : -162.5 -162.5 -162.5 -162.5 -162.5 -162.5 -162.5 -162.5 -162.5 -162.5"
    {"api getAln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    //fast
    {"fast getTxPsd"        , "(\\s+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getSnr"          , "(\\s+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    //fast getQln: "-101.5, -100.0, -100.5,  -99.0,  -98.5,  -98.5,  -99.5, -100.0,  -98.5, -100.5,..."
    {"fast getQln"          , "(\\s+-{,1}\\d{1,}\.\\d+,){1,10}\.{3}$"}, 
    {"fast getHlog"         , "(\\s+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getNoiseMargin"  , "(\\s+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getBitAlloc"     , "\\s+\\d{1,5}\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"fast getRmcBitAlloc"  , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"fast getAln"          , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    //bcm
    {"bcm getTxPsd"         , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"bcm getSnr"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"bcm getQln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"bcm getHlog"          , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"bcm getNoiseMargin"   , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"bcm getBitAlloc"      , "\\s+\\d{1,5}\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"bcm getRmcBitAlloc"   , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"bcm getAln"           , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"}
};

QString icvCmdSpecCharTbl[ICV_MAX_DATA_PATTERN_NUM][3]=
{
    {"rfc getTxPsd"         , "---", "-150.0" },
    {"rfc getSnr"           , "---", "0.0"    },
    {"rfc getQln"           , "NA" , "NA"     },
    {"rfc getHlog"          , "NA" , "NA"     },
    {"rfc getNoiseMargin"   , "NA" , "NA"     },
    {"rfc getBitAlloc"      , "NA" , "NA"     },
    {"rfc getRmcBitAlloc"   , "x"  , "0"      },
    {"rfc getAln"           , "NA" , "NA"     },
    //api
    {"api getTxPsd"         , "---", "-150.0" },
    {"api getSnr"           , "---", "0.0"    },
    {"api getQln"           , "NA" , "NA"     },
    {"api getHlog"          , "NA" , "NA"     },
    {"api getNoiseMargin"   , "NA" , "NA"     },
    {"api getBitAlloc"      , "NA" , "NA"     },
    {"api getRmcBitAlloc"   , "x"  , "0"      },
    {"api getAln"           , "NA" , "NA"     },
    //fast
    {"fast getTxPsd"        , "---", "-150.0" },
    {"fast getSnr"          , "---", "0.0"    },
    {"fast getQln"          , "NA" , "NA"     },
    {"fast getHlog"         , "NA" , "NA"     },
    {"fast getNoiseMargin"  , "NA" , "NA"     },
    {"fast getBitAlloc"     , "NA" , "NA"     },
    {"fast getRmcBitAlloc"  , "NA" , "NA"     },
    {"fast getAln"          , "NA" , "NA"     },
    //bcm
    {"bcm getTxPsd"         , "---", "-150.0" },
    {"bcm getSnr"           , "---", "0.0"    },
    {"bcm getQln"           , "NA" , "NA"     },
    {"bcm getHlog"          , "NA" , "NA"     },
    {"bcm getNoiseMargin"   , "NA" , "NA"     },
    {"bcm getBitAlloc"      , "NA" , "NA"     },
    {"bcm getRmcBitAlloc"   , "x"  , "0"      },
    {"bcm getAln"           , "NA" , "NA"     }
};
