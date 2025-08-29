#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QScrollArea>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QMap>
#include <QStringList>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>

class ImageViewer : public QMainWindow {
    Q_OBJECT
public:
    ImageViewer(QWidget* parent = nullptr);

private:
    void savePlaylists();
    void loadPlaylists();

    QListWidget* listWidget;
    QLabel* imageLabel;
    QScrollArea* scrollArea;
    QNetworkAccessManager manager;
    QTimer* slideshowTimer;
    double zoomFactor = 1.0;
        QPushButton* stopVideoBtn;

    int currentIndex = 0;

    QStringList imagePaths;
    QMap<QString, QStringList> playlists; // اسم القائمة -> مسارات الصور

    QMediaPlayer* videoPlayer;
    QVideoWidget* videoWidget;

    void scanFolder(const QString& folderPath);
    void displayImage();
    void updatePlaylistView();

private slots:
    void openFolder();
    void openFile();
    void addImageFromUrl();
    void showImage(QListWidgetItem* item);
    void zoomIn();
    void zoomOut();
    void startSlideshow();
    void nextSlide();
    void createPlaylist();
    void addToPlaylist();
    void playVideo(const QString& path);
    void searchImages(const QString& keyword);
};
