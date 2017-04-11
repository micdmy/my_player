#include "medialibrary.h"

MediaLibrary::MediaLibrary(QObject *parent) : QObject(parent)
{
    SongInfo::setUsedTags(QStringList());


}

MediaLibrary::~MediaLibrary()
{
    delete songsFilterModel;
}



void MediaLibrary::editDirectories()
{
    LibraryDirectoriesDialog editDirectoriesDialog(&dirModel);
    connect(&editDirectoriesDialog,SIGNAL(directoriesChanged(QStringList,QStringList)),this,SLOT(reloadDirectories(QStringList,QStringList)));
    editDirectoriesDialog.exec();
    saveSettings();
}

void MediaLibrary::reloadAllDirectories()
{
    PathScanner pathScanner;
    songsModel.removeAllSongs();
    for(QString path : dirModel.getList()) {
        songsModel.addSongs(pathScanner.scanDirectory(path,fileFormats));
    }
    saveSongs();
    songsModel.emitAllDataChanged();
}

void MediaLibrary::reloadDirectories(QStringList addDirs, QStringList removeDirs)
{
    //this function should be rewritten in future to implement removing directories
    if(!(addDirs.isEmpty() && removeDirs.isEmpty())) {
        PathScanner pathScanner;
        /*
         * if removeDirs is not empty reloads all dirs from dirModel
         */
        if(removeDirs.isEmpty()) { //only add songs from addDirs
            for(QString path : addDirs) {
                songsModel.addSongs(pathScanner.scanDirectory(path,fileFormats));
            }
        } else { //reload all dirs
            songsModel.removeAllSongs();
            for(QString path : dirModel.getList()) {
                songsModel.addSongs(pathScanner.scanDirectory(path,fileFormats));
            }
        }
        saveSongs();
        songsModel.emitAllDataChanged();
    }
}

void MediaLibrary::editUsedTags()
{
    QStringListModel model(tags);
    StringListDialog dialog(&model, "Set used tags ",
                            "Set tags which are read \nwhile scanning source directories.\nI.e.: artist\nFor changes to take place,\nreload library!");
    dialog.exec();
    if(tags != model.stringList()) {
        tags = model.stringList();
        saveSettings();
        if(ErrGui::ask("Tags have been changed.\nReload library with new tags?")) {
            songsModel.setColumns(tags);
            reloadAllDirectories();
        }
    }
}

void MediaLibrary::editUsedFileFormats()
{
    QStringListModel model(fileFormats);
    StringListDialog dialog(&model, "Set used file formats (i.e *.mp3)",
                            "Set file formats of files to read \nwhile scanning source directories.\nI.e.: *.mp3\nFor changes to take place,\nreload library!");
    dialog.exec();
    if(fileFormats != model.stringList()) {
        fileFormats = model.stringList();
        saveSettings();
        if(ErrGui::ask("File formats have been changed.\nReload library?")) {
            reloadAllDirectories();
        }
    }


}

void MediaLibrary::setDefaultTagsAndFileFormats()
{
    setDefaultFileFormats();
    setDefaultTags();
    saveSettings();
}

void MediaLibrary::reloadExtraFiltersValues(QStringList & tags)
{
    clearExtraFiltersValues(); //deletes previous objects in this QHash
    for(QString tag : tags) {
        QStringList * valuesOfTheTag = new QStringList();
        songsModel.findAllValuesOfTag(tag,valuesOfTheTag);
        extraFiltersValues.insert(tag,valuesOfTheTag);
    }
}

void MediaLibrary::saveSongs()
{
    QFile file(ProgramPaths::mediaLibrarySongsList());
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << songsModel;
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
            in >> songsModel;
            file.close();      
        } else {
            ErrGui::error(file);
        }
    } else {
        ErrGui::error(file);
    }
}

int MediaLibrary::loadSettings()
{
    QFile file(ProgramPaths::mediaLibrarySettings());
    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in >> tags;
            in >> fileFormats;
            in >> dirModel;
            file.close();
            return 1;
        } else {
            ErrGui::error(file);
        }
    }
    return 0;
}

void MediaLibrary::setDefaultTags()
{
    tags << "title" << "album" << "artist";
}

void MediaLibrary::setDefaultFileFormats()
{
    fileFormats << "*.mp3" << "*.flac" << "*.wma";
}

void MediaLibrary::clearExtraFiltersValues()
{
    for(auto key : extraFiltersValues.keys()) {
        delete extraFiltersValues.value(key);
    }
    extraFiltersValues.clear();
}

void MediaLibrary::load()
{
    if(loadSettings()) {
       //loaded, ok
       songsModel.setColumns(tags);
       loadSongs();
    } else {
        setDefaultTagsAndFileFormats();
        songsModel.setColumns(tags);
        if(ErrGui::ask("Media library never configured.\n Add directories to library now?")) {
            editDirectories();
        }
    }
}

SongsInLibrary *MediaLibrary::getDataModelPtr()
{
    return &songsModel;
}

SongsInLibrarySortFilter *MediaLibrary::getProxyModel()
{
    return songsFilterModel;
}

void MediaLibrary::initProxyModel()
{
    songsFilterModel = new SongsInLibrarySortFilter(this);
    songsFilterModel->setSourceModel(&songsModel);
}

void MediaLibrary::setupProxyModel(QItemSelectionModel * selectionModel, SearchFrame * filterChangedSender)
{
    songsFilterModel->setSelectionModel(selectionModel);
    connect(filterChangedSender,SIGNAL(searchTextChanged(QString)),songsFilterModel,SLOT(filterChanged(QString)));
}




