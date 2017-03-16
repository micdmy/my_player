#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include <QObject>
#include <QFileDialog>
#include <QLineEdit>
#include <QHeaderView>
#include "programpaths.h"
#include "librarydirectoriesdialog.h"
#include "directorieslistmodel.h"
#include "songsinlibrary.h"
#include "songsinlibrarysortfilter.h"
#include "pathscanner.h"
#include "stringlistdialog.h"
class MediaLibrary : public QObject
{
    Q_OBJECT
public:
    explicit MediaLibrary(QObject *parent = 0);
    ~MediaLibrary();
    void    load(void);
    SongsInLibrary * getDataModelPtr(void);
    SongsInLibrarySortFilter * getProxyModel(void);
    void initProxyModel(void);
    void setupProxyModel(QItemSelectionModel * selectionModel, QLineEdit *filterChangedSender);
private:
    DirectoriesListModel dirModel;
    SongsInLibrary songsModel;
    SongsInLibrarySortFilter * songsFilterModel;
    void    saveSongs(void);
    void    saveSettings(void);
    void    loadSongs(void);
    int     loadSettings(void);
    void setDefaultTags();
    void setDefaultFileFormats();
    QStringList tags, fileFormats;
signals:

public slots:
    void    editDirectories(void);
    void    reloadAllDirectories(void);
    void    editUsedTags(void);
    void    editUsedFileFormats(void);
    void    setDefaultTagsAndFileFormats();
private slots:
void    reloadDirectories(QStringList add, QStringList removeList);
};

#endif // MEDIALIBRARY_H
