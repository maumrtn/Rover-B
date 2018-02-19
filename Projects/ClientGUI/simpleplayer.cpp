/*
* VLC-Qt Simple Player
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*/

#include <QFileDialog>
#include <QInputDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>


#include "simpleplayer.h"

SimplePlayer::SimplePlayer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::SimplePlayer),
      _media(0),
      _equalizerDialog(new EqualizerDialog(this))
{


    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->seek->setMediaPlayer(_player);

    connect(ui->openUrl, &QPushButton::clicked, this, &SimplePlayer::openUrl);

}

SimplePlayer::~SimplePlayer()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}


void SimplePlayer::openUrl()
{
    QString url =
            QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));

    if (url.isEmpty())
        return;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
}

