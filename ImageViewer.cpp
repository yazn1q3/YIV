#include "ImageViewer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDirIterator>
#include <QPixmap>
#include <QInputDialog>
#include <QNetworkReply>
#include <QBuffer>
#include <QFile>
#include <QMessageBox>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIcon>
ImageViewer::ImageViewer(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
QIcon icon(":/icons/app_logo.png");  // لو ضايفها في resources
this->setWindowTitle("Yaznbook Image Viewer");  // 👈 هنا العنوان
    // Scrollable image area
    this->setWindowIcon(icon);
    scrollArea = new QScrollArea();
    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true);

    // Video support
    videoPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoPlayer->setVideoOutput(videoWidget);

    // Apply styles AFTER creating widgets
    scrollArea->setStyleSheet("background-color: black;");
    imageLabel->setStyleSheet("background-color: transparent;");
    videoWidget->setStyleSheet("background-color: black;");

    // Playlist/List view
    listWidget = new QListWidget();

    // Top buttons
    QHBoxLayout* topLayout = new QHBoxLayout();
    QPushButton* openFolderBtn = new QPushButton("Open Folder");
    QPushButton* openFileBtn = new QPushButton("Open File");
    QPushButton* addUrlBtn = new QPushButton("Add Image from URL");
    QPushButton* zoomInBtn = new QPushButton("Zoom In");
    QPushButton* zoomOutBtn = new QPushButton("Zoom Out");
    QPushButton* slideshowBtn = new QPushButton("Slideshow");
    QPushButton* stopSlideshowBtn = new QPushButton("Stop Slideshow");
    QPushButton* createPlaylistBtn = new QPushButton("Create Playlist");
    QPushButton* addToPlaylistBtn = new QPushButton("Add to Playlist");
    QPushButton* seePlaylistsBtn = new QPushButton("See All Playlists");
    QLineEdit* searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Search Images...");

    topLayout->addWidget(openFolderBtn);
    topLayout->addWidget(openFileBtn);
    topLayout->addWidget(addUrlBtn);
    topLayout->addWidget(zoomInBtn);
    topLayout->addWidget(zoomOutBtn);
    topLayout->addWidget(slideshowBtn);
    topLayout->addWidget(stopSlideshowBtn);
    topLayout->addWidget(createPlaylistBtn);
    topLayout->addWidget(addToPlaylistBtn);
    topLayout->addWidget(seePlaylistsBtn);
    topLayout->addWidget(searchEdit);

stopVideoBtn = new QPushButton("Stop Video", videoWidget); 
stopVideoBtn->setStyleSheet("background-color: red; color: white; padding: 5px; border-radius: 8px;");
stopVideoBtn->setFixedSize(120, 40);
stopVideoBtn->move(10, 10); // 👈 يحدد مكانه فوق الفيديو
stopVideoBtn->hide();

topLayout->addWidget(stopVideoBtn);

// Connect stop video button

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(listWidget);

    setCentralWidget(central);
connect(stopVideoBtn, &QPushButton::clicked, [this](){
    videoPlayer->stop();
    videoWidget->hide();
    imageLabel->show();
    scrollArea->show();
    stopVideoBtn->hide();
});
    // Connections
    connect(listWidget, &QListWidget::itemClicked, this, &ImageViewer::showImage);
    connect(openFolderBtn, &QPushButton::clicked, this, &ImageViewer::openFolder);
    connect(openFileBtn, &QPushButton::clicked, this, &ImageViewer::openFile);
    connect(addUrlBtn, &QPushButton::clicked, this, &ImageViewer::addImageFromUrl);
    connect(zoomInBtn, &QPushButton::clicked, this, &ImageViewer::zoomIn);
    connect(zoomOutBtn, &QPushButton::clicked, this, &ImageViewer::zoomOut);
    connect(slideshowBtn, &QPushButton::clicked, this, &ImageViewer::startSlideshow);
    connect(stopSlideshowBtn, &QPushButton::clicked, [this](){
        if(slideshowTimer->isActive()) slideshowTimer->stop();
    });
    connect(createPlaylistBtn, &QPushButton::clicked, this, &ImageViewer::createPlaylist);
    connect(addToPlaylistBtn, &QPushButton::clicked, this, &ImageViewer::addToPlaylist);
    connect(seePlaylistsBtn, &QPushButton::clicked, [this](){
        if(playlists.isEmpty()){
            QMessageBox::information(this,"Playlists","No playlists created yet!");
            return;
        }
        QString allLists;
        for(const QString &key: playlists.keys()){
            allLists += key + " (" + QString::number(playlists[key].size()) + " items)\n";
        }
        QMessageBox::information(this,"Playlists",allLists);
    });
    connect(searchEdit, &QLineEdit::textChanged, this, &ImageViewer::searchImages);

    // Initialize slideshow timer
    slideshowTimer = new QTimer(this);
    connect(slideshowTimer, &QTimer::timeout, this, &ImageViewer::nextSlide);

    // Scan default folder
    scanFolder(QDir::homePath() + "/Pictures");
    loadPlaylists();

}

void ImageViewer::scanFolder(const QString& folderPath) {
    QDirIterator it(folderPath, QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.gif" << "*.bmp" << "*.webp" << "*.mp4" << "*.mkv", QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext()){
        QString path = it.next();
        QFileInfo info(path);
        listWidget->addItem(info.fileName());
        imagePaths.append(path);
    }
}

void ImageViewer::openFolder() { 
    QString folder = QFileDialog::getExistingDirectory(this, "Select Folder");
    if(!folder.isEmpty()) scanFolder(folder);
}

void ImageViewer::openFile() {
    QStringList files = QFileDialog::getOpenFileNames(this,"Select Files","","Images/Videos (*.png *.jpg *.jpeg *.gif *.bmp *.webp *.mp4 *.mkv)");
    for(const QString &file: files){
        QFileInfo info(file);
        listWidget->addItem(info.fileName());
        imagePaths.append(file);
    }
}



void ImageViewer::addImageFromUrl(){
    bool ok;
    QString url = QInputDialog::getText(this,"Add from URL","Enter URL:",QLineEdit::Normal,"",&ok);
    if(ok && !url.isEmpty()){
        QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
        connect(reply,&QNetworkReply::finished,[this,reply,url](){
            QByteArray data = reply->readAll();
            QPixmap pix;
            pix.loadFromData(data);
            if(!pix.isNull()){
                QString fileName = QFileInfo(QUrl(url).path()).fileName();
                listWidget->addItem(fileName);
                QString tempPath = QDir::tempPath() + "/" + fileName;
                QFile f(tempPath);
                if(f.open(QIODevice::WriteOnly)){
                    f.write(data);
                    f.close();
                    imagePaths.append(tempPath);
                }
            } else {
                QMessageBox::warning(this,"Error","Failed to load image!");
            }
            reply->deleteLater();
        });
    }
}

void ImageViewer::showImage(QListWidgetItem* item){
    currentIndex = listWidget->row(item);
    QString path = imagePaths[currentIndex];
    if(path.endsWith(".mp4") || path.endsWith(".mkv")){
        playVideo(path);
    }else{
        displayImage();
    }
}

void ImageViewer::displayImage(){
    if(videoWidget->isVisible()) videoWidget->hide(); 
    stopVideoBtn->hide();
    imageLabel->show();
    scrollArea->show();

    // إذا ما فيه صور
    if(currentIndex < 0 || currentIndex >= imagePaths.size()){
        QUrl logoUrl("https://icons.iconarchive.com/icons/itzikgur/my-seven/256/Pictures-Nikon-icon.png");
        QNetworkReply* reply = manager.get(QNetworkRequest(logoUrl));
        connect(reply, &QNetworkReply::finished, [=](){
            QByteArray data = reply->readAll();
            QPixmap defaultLogo;
            defaultLogo.loadFromData(data);
            if(!defaultLogo.isNull()){
                imageLabel->setPixmap(defaultLogo.scaled(scrollArea->width()*0.5,
                                                         scrollArea->height()*0.5,
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
            } else {
                imageLabel->setText("Failed to load logo!");
            }
            reply->deleteLater();
        });
        return;
    }

    QPixmap pix(imagePaths[currentIndex]);
    if(pix.isNull()){
        // لو الصورة الحالية فشلت نعرض اللوجو الافتراضي بنفس الطريقة
        QUrl logoUrl("https://icons.iconarchive.com/icons/itzikgur/my-seven/256/Pictures-Nikon-icon.png");
        QNetworkReply* reply = manager.get(QNetworkRequest(logoUrl));
        connect(reply, &QNetworkReply::finished, [=](){
            QByteArray data = reply->readAll();
            QPixmap defaultLogo;
            defaultLogo.loadFromData(data);
            if(!defaultLogo.isNull()){
                imageLabel->setPixmap(defaultLogo.scaled(scrollArea->width()*0.5,
                                                         scrollArea->height()*0.5,
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
            } else {
                imageLabel->setText("Failed to load logo!");
            }
            reply->deleteLater();
        });
        return;
    }

    // --- باقي الكود للانيميشن ---
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(imageLabel);
    imageLabel->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect,"opacity");
    anim->setDuration(700);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* scaleAnim = new QPropertyAnimation(imageLabel, "geometry");
    QRect startRect = imageLabel->geometry();
    scaleAnim->setDuration(700);
    scaleAnim->setStartValue(QRect(startRect.x(), startRect.y(),
                                   startRect.width()*0.8, startRect.height()*0.8));
    scaleAnim->setEndValue(startRect);
    scaleAnim->setEasingCurve(QEasingCurve::OutBack);
    scaleAnim->start(QAbstractAnimation::DeleteWhenStopped);

    imageLabel->setPixmap(pix.scaled(scrollArea->width()*zoomFactor-20,
                                     scrollArea->height()*zoomFactor-20,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation));
}



void ImageViewer::zoomIn(){ zoomFactor *= 1.25; displayImage(); }
void ImageViewer::zoomOut(){ zoomFactor /= 1.25; displayImage(); }

void ImageViewer::startSlideshow(){
    if(slideshowTimer->isActive()){
        slideshowTimer->stop();
    }else if(!imagePaths.isEmpty()){
        slideshowTimer->start(3000);
        currentIndex = -1;
        nextSlide();
    }
}

void ImageViewer::nextSlide(){
    if(imagePaths.isEmpty()) return;
    currentIndex = (currentIndex+1)%imagePaths.size();
    showImage(listWidget->item(currentIndex));
}

void ImageViewer::createPlaylist(){
    bool ok;
    QString name = QInputDialog::getText(this,"Create Playlist","Playlist name:",QLineEdit::Normal,"",&ok);
    if(ok && !name.isEmpty()) playlists[name] = QStringList();
    savePlaylists();

}

void ImageViewer::addToPlaylist(){
    if(playlists.isEmpty()) return;
    bool ok;
    QStringList keys = playlists.keys();
    QString pl = QInputDialog::getItem(this,"Select Playlist","Add to:",keys,0,false,&ok);
    if(ok && currentIndex>=0 && currentIndex<imagePaths.size()){
        playlists[pl].append(imagePaths[currentIndex]);
    }
    savePlaylists();

}

void ImageViewer::savePlaylists() {
    QJsonObject root;
    for (auto it = playlists.begin(); it != playlists.end(); ++it) {
        QJsonArray arr;
        for (const QString &path : it.value()) arr.append(path);
        root[it.key()] = arr;
    }

    QJsonDocument doc(root);
    QFile file(QDir::homePath() + "/.imageviewer_playlists.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void ImageViewer::loadPlaylists() {
    QFile file(QDir::homePath() + "/.imageviewer_playlists.json");
    if (!file.exists()) return;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject root = doc.object();
            for (auto it = root.begin(); it != root.end(); ++it) {
                QString name = it.key();
                QJsonArray arr = it.value().toArray();
                QStringList list;
                for (auto val : arr) list.append(val.toString());
                playlists[name] = list;
            }
        }
    }
}


void ImageViewer::playVideo(const QString& path){
    // Hide images
    imageLabel->hide();
    scrollArea->hide();

    videoWidget->resize(scrollArea->size());
    videoWidget->show();
    stopVideoBtn->show(); // إظهار زر الإيقاف

    videoPlayer->setMedia(QUrl::fromLocalFile(path));
    videoPlayer->play();

    // Animation smooth fade in for video
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(videoWidget);
    videoWidget->setGraphicsEffect(effect);
    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(600);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ImageViewer::searchImages(const QString& keyword){
    listWidget->clear();
    for(const QString &path: imagePaths){
        QFileInfo info(path);
        if(info.fileName().contains(keyword,Qt::CaseInsensitive)){
            listWidget->addItem(info.fileName());
        }
    }
}
