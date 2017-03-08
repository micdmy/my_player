#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <QObject>
#include <QFileDialog>
#include "programpaths.h"
#include "librarydirectoriesdialog.h"
#include "directorieslistmodel.h"
#include "songsinlibrary.h"
#include "pathscanner.h"
#include "stringlistdialog.h"
class MediaLibrary : public QObject
{
    Q_OBJECT
public:
    explicit MediaLibrary(QObject *parent = 0);
    ~MediaLibrary();
    void    load(void);
private:
    DirectoriesListModel dirModel;
    SongsInLibrary songs;
    void    saveSongs(void);
    void    saveSettings(void);
    void    loadSongs(void);
    void    loadSettings(void);
    void setDefaultTags();
    void setDefaultFileFormats();
    QStringList tags, fileFormats;
signals:

public slots:
    void    addDirectory(void);
    void    editDirectories(void);
    void    reloadAllDirectories(void);
    void    editUsedTags(void);
    void    editUsedFileFormats(void);
    void    setDefaultTagsAndFileFormats();
private slots:
void    reloadDirectories(QStringList directories);
};

#endif // MEDIALIBRARY_H
