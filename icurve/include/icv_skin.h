#pragma once
#include <QString>

class IcvSkin
{
public:
    IcvSkin(void);
    ~IcvSkin(void);

    QString GetSkinCss();
private:
    QString skinCss;
};
