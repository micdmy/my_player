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
#include "searchframe.h"
#include "onetagtablemodel.h"
#include "onetagsortfilter.h"
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
    void setupProxyModel(QItemSelectionModel * selectionModel, SearchFrame *filterChangedSender);
    QList<OneTagSortFilter *> getOneTagSortFilters(void);
private:
    DirectoriesListModel dirModel;
    SongsInLibrary songsModel; //TODO dostaje sygnal , zmienia headery
    SongsInLibrarySortFilter * songsFilterModel; //TODO daje sygnal
    void    saveSongs(void);
    void    saveSettings(void);
    void    loadSongs(void);
    int     loadSettings(void);
    void setDefaultTags();
    void setDefaultFileFormats();
    QStringList tags, fileFormats;
    QHash<QString,QStringList*> extraFiltersValues; //<tag, list of existing values of this tag in library>
    void clearExtraFiltersValues(void);
    void reloadExtraFiltersValues(QStringList & tags);
    QList<OneTagTableModel *> oneTagTableModels;
    QList<OneTagSortFilter *> oneTagSortFilters;
    void deleteOneTagModelsAndFilters(void);

public slots:
    void    editDirectories(void);
    void    reloadAllDirectories(void);
    void    editUsedTags(void);
    void    editUsedFileFormats(void);
    void    setDefaultTagsAndFileFormats(void);
    void    reloadOneTagTableModels(QStringList & tags); //TODO do podlaczenia z sygnalem
private slots:
    void    reloadDirectories(QStringList add, QStringList removeList);
};

#endif // MEDIALIBRARY_H
