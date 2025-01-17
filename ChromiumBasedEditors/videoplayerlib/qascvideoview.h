#ifndef QASCIMAGEVIEW_H
#define QASCIMAGEVIEW_H

#include <QWidget>
#include <QLabel>

#include <QDir>
#include <QFileInfo>
#include <QResizeEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QMediaPlayer>
#include "src/qascmediaplayer.h"

#include <QtCore/QtGlobal>

#if defined(BUILD_VIDEO_LIBRARY)
#  define VIDEO_LIB_EXPORT Q_DECL_EXPORT
#else
#  define VIDEO_LIB_EXPORT Q_DECL_IMPORT
#endif

namespace NSBaseVideoLibrary
{
    VIDEO_LIB_EXPORT void Init(QObject* parent);
    VIDEO_LIB_EXPORT void Destroy();
    VIDEO_LIB_EXPORT void* GetLibrary();
}

class QAscVideoView_Private;
class VIDEO_LIB_EXPORT QAscVideoView : public QWidget
{
    Q_OBJECT
public:
    explicit QAscVideoView(QWidget *parent, int r, int g, int b);
    virtual ~QAscVideoView();

public:
    virtual void resizeEvent(QResizeEvent* e);

    virtual void paintEvent(QPaintEvent *);

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

#if defined(_LINUX) && !defined(_MAC)
    virtual void mouseMoveEvent(QMouseEvent* e);
#endif

    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

    virtual bool getMainWindowFullScreen();
    virtual void setMainWindowFullScreen(bool bIsFullScreen);
    virtual QWidget* getMainWindow();

public:
    void PlayPause();
    void Volume();
    void Fullscreen();
    void Playlist(double duration = 100);
    void SavePlayListAddons(const QString& sAddon);
    
    void AddFilesToPlaylist(QStringList& files, const bool isStart = false);
	void LoadPlaylist();
    void SavePlaylist();

    void setFooterVisible(bool isVisible);

    void setPlayListUsed(bool isUsed);
    void setFullScreenUsed(bool isUsed);
    void setPresentationMode(bool isPresentationMode);
    void setMedia(QString sMedia);

    void Stop();

signals:
    void OnTitleChanged(const QString& sTitle);

public slots:
    void slotPlayPause();
    void slotVolume();
    void slotFullscreen();
    void slotPlaylist();
    void slotVolumeChanged(int nValue);
    void slotSeekChanged(int nValue);

    void slotOpenFile(QString sFile);

    void slotPlayerPosChanged(int nPos);
    void slotPlayerStateChanged(QMediaPlayer_State state);
    void slotVideoAvailableChanged(bool videoAvailable);

protected:
    void UpdatePlayPause();

public:
    QAscVideoView_Private* m_pInternal;
};

#endif // QASCIMAGEVIEW_H
