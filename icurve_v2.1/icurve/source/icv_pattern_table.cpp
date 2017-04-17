#include <QString>
#include "icv_pattern_table.h"

QString icvCmdTitlePatternTbl[ICV_MAX_TITLE_PATTERN_NUM]=
{
    "(rfc|bcm|api|fast).+(getTxPsd|getSnr|getQln|getHlog|getNoiseMargin|getBitAlloc|getRmcBitAlloc|getAln)\\s+([0-9]+)\\s+([0-1])\\s*.*$"
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
    {"api getAln"           , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    //fast
    {"fast getTxPsd"        , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getSnr"          , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getQln"          , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getHlog"         , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getNoiseMargin"  , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getBitAlloc"     , "\\s+\\d{1,5}\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"fast getRmcBitAlloc"  , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    {"fast getAln"          , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
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
    {"rfc getSnr"           , "NA" , "NA"     },
    {"rfc getQln"           , "NA" , "NA"     },
    {"rfc getHlog"          , "NA" , "NA"     },
    {"rfc getNoiseMargin"   , "NA" , "NA"     },
    {"rfc getBitAlloc"      , "NA" , "NA"     },
    {"rfc getRmcBitAlloc"   , "x"  , "0"      },
    {"rfc getAln"           , "NA" , "NA"     },
    //api
    {"api getTxPsd"         , "NA" , "NA"     },
    {"api getSnr"           , "NA" , "NA"     },
    {"api getQln"           , "NA" , "NA"     },
    {"api getHlog"          , "NA" , "NA"     },
    {"api getNoiseMargin"   , "NA" , "NA"     },
    {"api getBitAlloc"      , "NA" , "NA"     },
    {"api getRmcBitAlloc"   , "x"  , "0"      },
    {"api getAln"           , "NA" , "NA"     },
    //fast
    {"fast getTxPsd"        , "NA" , "NA"     },
    {"fast getSnr"          , "NA" , "NA"     },
    {"fast getQln"          , "NA" , "NA"     },
    {"fast getHlog"         , "NA" , "NA"     },
    {"fast getNoiseMargin"  , "NA" , "NA"     },
    {"fast getBitAlloc"     , "NA" , "NA"     },
    {"fast getRmcBitAlloc"  , "NA" , "NA"     },
    {"fast getAln"          , "NA" , "NA"     },
    //bcm
    {"bcm getTxPsd"         , "NA" , "NA"     },
    {"bcm getSnr"           , "NA" , "NA"     },
    {"bcm getQln"           , "NA" , "NA"     },
    {"bcm getHlog"          , "NA" , "NA"     },
    {"bcm getNoiseMargin"   , "NA" , "NA"     },
    {"bcm getBitAlloc"      , "NA" , "NA"     },
    {"bcm getRmcBitAlloc"   , "x"  , "0"      },
    {"bcm getAln"           , "NA" , "NA"     }
};