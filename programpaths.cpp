#include "programpaths.h"



QString ProgramPaths::mediaLibrarySettings()
{
    return  getFixAppConfigDir() + QString(mediaLibrarySet);
}

QString ProgramPaths::mediaLibrarySongsList()
{
    return  getFixAppConfigDir() + QString(mediaLibrarySList);
}

QString ProgramPaths::getFixAppConfigDir()
{
    QString configDirPath = writableLocation(AppConfigLocation);
    QDir dir(configDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
        QFile file(configDirPath + "/readme");
        if(file.open(QIODevice::WriteOnly)) {
            file.write(ProgramPaths::readmeContent);
            file.close();
        } else {
            ErrGui::error(file);
        }
    }
    return configDirPath;
}
