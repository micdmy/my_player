#include "medialibrary.h"

MediaLibrary::MediaLibrary(QObject *parent) : QObject(parent)
{

}

MediaLibrary::~MediaLibrary()
{

}

void MediaLibrary::addDirectory()
{
    QString newDirectory = dirModel.add();
    saveSettings();
    reloadDirectories(QStringList(newDirectory));
}

void MediaLibrary::editDirectories()
{
    LibraryDirectoriesDialog editDirectoriesDialog(&dirModel);
    connect(&editDirectoriesDialog,SIGNAL(directoriesAdded(QStringList)),this,SLOT(reloadDirectories(QStringList)));
    editDirectoriesDialog.exec();
    saveSettings();
}

void MediaLibrary::reloadAllDirectories()
{
    reloadDirectories(dirModel.getList());
}

void MediaLibrary::reloadDirectories(QStringList directories)
{
    SongInfo::setUsedTags(tags);
    PathScanner pathScanner;
    for(QString path : directories) {
        songs.setSongs(pathScanner.scanDirectory(path,fileFormats));
    }
    saveSongs();
}

void MediaLibrary::editUsedTags()
{
    QStringListModel model(tags);
    StringListDialog dialog(&model, "Set used tags ",
                            "Set tags which are read \nwhile scanning source directories.\nI.e.: artist\nFor changes to take place,\nreload library!");
    dialog.exec();
    tags = model.stringList();
    saveSettings();
}

void MediaLibrary::editUsedFileFormats()
{
    QStringListModel model(fileFormats);
    StringListDialog dialog(&model, "Set used file formats (i.e *.mp3)",
                            "Set file formats of files to read \nwhile scanning source directories.\nI.e.: *.mp3\nFor changes to take place,\nreload library!");
    dialog.exec();
    fileFormats = model.stringList();
    saveSettings();
}

void MediaLibrary::setDefaultTagsAndFileFormats()
{
    setDefaultFileFormats();
    setDefaultTags();
    saveSettings();
}

void MediaLibrary::saveSongs()
{
    QFile file(ProgramPaths::mediaLibrarySongsList());
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << songs;
        file.close();
    } else{
        ErrGui::error(file);
    }

}

void MediaLibrary::saveSettings()
{
    QFile file(ProgramPaths::mediaLibrarySettings());
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << tags;
        out << fileFormats;
        out << dirModel;
        file.close();
    } else{
        ErrGui::error(file);
    }
}

void MediaLibrary::loadSongs()
{
    QFile file(ProgramPaths::mediaLibrarySongsList());
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in >> songs;
            file.close();
        } else {
            ErrGui::error(file);
        }
    }
}

void MediaLibrary::loadSettings()
{
    QFile file(ProgramPaths::mediaLibrarySettings());
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in >> tags;
            in >> fileFormats;
            in >> dirModel;
            file.close();
        } else {
            ErrGui::error(file);
        }
    }  else {
        setDefaultTagsAndFileFormats();
        if(ErrGui::ask("Media library not configured.\n Add directories to library now?")) {
            addDirectory();
        }
    }
}

void MediaLibrary::setDefaultTags()
{
    tags << "title" << "album" << "artist";
}

void MediaLibrary::setDefaultFileFormats()
{
    fileFormats << "*.mp3" << "*.flac" << "*.wma";
}

void MediaLibrary::load()
{
    loadSettings();
    loadSongs();
}




