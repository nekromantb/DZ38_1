#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaContent>


class CircleWidget:public QPushButton {
Q_OBJECT
public:
    CircleWidget() = default;
    CircleWidget(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void KeyPressEvent(QKeyEvent *e);

    QString getPath()
    {
        return clickPath;
    }
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonGreenPixmap;
    QPixmap mButtonYellowPixmap;
    QString clickPath;
    bool isDown = false;
};

CircleWidget::CircleWidget(QWidget *parent) {
    setParent(parent);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonGreenPixmap = QPixmap("G:\\work\\Prog\\progs\\DZ38_1\\greenButton.png");
    mButtonYellowPixmap = QPixmap("G:\\work\\Prog\\progs\\DZ38_1\\yellowButton.png");
    clickPath = QString("G:\\work\\Prog\\progs\\DZ38_1\\Click.mp3");
    mCurrentButtonPixmap = mButtonGreenPixmap;

    setGeometry(mCurrentButtonPixmap.rect());
    connect(this, &QPushButton::clicked, this, &CircleWidget::setDown);
}

void CircleWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize CircleWidget::sizeHint() const {
    return QSize (200,250);
}

QSize CircleWidget::minimumSizeHint() const {
    return QSize (100,100);
}

void CircleWidget::setUp() {
    mCurrentButtonPixmap = mButtonGreenPixmap;
    update();
}

void CircleWidget::setDown() {
    mCurrentButtonPixmap = mButtonYellowPixmap;
    update();
    QTimer::singleShot(1000, this, &CircleWidget::setUp);
}

void CircleWidget::KeyPressEvent(QKeyEvent *e) {
    setDown();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget appWindow;
    CircleWidget paint(&appWindow);

    auto *player = new QMediaPlayer(&appWindow);
    player->setVolume(75);
    player->setMedia(QUrl::fromLocalFile(paint.getPath()));

    QWidget::connect(&paint, &QPushButton::clicked, player, &QMediaPlayer::play);

    appWindow.setFixedSize (200, 250);
    appWindow.move (2000, 500);

    appWindow.show();
    return app.exec();
}
#include "main.moc"
