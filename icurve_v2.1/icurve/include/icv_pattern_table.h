#ifndef ICV_PATTERN_TABLE_H
#define ICV_PATTERN_TABLE_H
#include <QString>

#define ICV_MAX_DATA_PATTERN_NUM   (100)
#define ICV_MAX_TITLE_PATTERN_NUM  (20)

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
    {"api getRmcBitAlloc"   , "\\s+\\d{1,5}\\s*:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}\\s*$"},
    {"api getAln"           , "\\s+\\d+\\s*:(\\s+\\d+){1,20}\\s*$"},
    //fast
    {"fast getTxPsd"        , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getSnr"          , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getQln"          , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getHlog"         , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getNoiseMargin"  , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getBitAlloc"     , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
    {"fast getRmcBitAlloc"  , "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}\\s*$"},
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

QString icvCmdTitlePatternTbl[ICV_MAX_TITLE_PATTERN_NUM]=
{
    "(rfc|bcm|api|fast).+(getTxPsd|getSnr|getQln|getHlog|getNoiseMargin|getBitAlloc|getRmcBitAlloc|getAln)\\s+([0-9]+)\\s+([0-1])\\s*.*$"
};
#endif
