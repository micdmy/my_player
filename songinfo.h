#ifndef SONGINFO_H
#define SONGINFO_H
#include <QHash>
#include <QString>
#include <QStringList>
#include <QDataStream>
#include <taglib/tpropertymap.h>
#include <taglib/fileref.h>
#include <taglib/tstring.h>
//#include <taglib/tfilestream.h>
#include <taglib/audioproperties.h>
#include <taglib/tag.h>
//#include <taglib/tag_c.h>
//#include <taglib/taglib.h>
//#include <taglib/taglib_config.h>
//#include <taglib/taglib_export.h>

class SongInfo : public QObject
{
public:
    SongInfo(QObject * parent=0);
    SongInfo(const QString & path);
    SongInfo(const SongInfo& s);
    SongInfo & operator =(const SongInfo& s);
    QString getMetadata(const QString &key);
    QString &getMetadata(int column);
    void setMetadata(const QString &key, QString &value);
    static void setUsedTags(const QStringList & tags);
    static int getUsedTagsCount(void);
    static QString & getUsedTag(int index);
    static QStringList &getUsedTags();
    QString getPath();
    void setPath(const QString &path);
    void readFile();

    //reading from QDataStream:
    friend QDataStream & operator>>(QDataStream & dStream, SongInfo & songInfo);
    //saving to QDataStream:
    friend QDataStream & operator<<(QDataStream & dStream,const SongInfo & songInfo);
     //copy of used Tags for convinient use in QT
private:
    QHash<QString,QString> data;
    static TagLib::StringList usedTags;
    static QStringList usedTagsQ;
    static QString emptyString;
    void clearDataExceptPath();
};

#endif // SONGINFO_H
