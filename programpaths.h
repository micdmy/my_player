#ifndef PROGRAMPATHS_H
#define PROGRAMPATHS_H
#define README_TEXT "This folder contains user specific files\n for program My Player.";
#include<QStandardPaths>
#include<QDir>
#include<QFile>
#include<QErrorMessage>
#include"errgui.h"
class ProgramPaths : public QStandardPaths
{
public:
    static QString mediaLibrarySettings();
    static QString mediaLibrarySongsList();
private:
    static QString getFixAppConfigDir();
    static constexpr const char* mediaLibrarySet = "/medialibrarysettings.dat";
    static constexpr const char* mediaLibrarySList = "/medialibrarysongslist.dat";
    static constexpr const char* readmeContent = README_TEXT;
};
#endif // PROGRAMPATHS_H
