#ifndef MYVIDEOSTREAM_H
#define MYVIDEOSTREAM_H
#include <VLCQtCore/VideoStream.h>
#include "stdio.h"



class MyVideoStream : public VlcVideoStream
{
public:
    MyVideoStream();
private slots:
    void frameUpdated();

};

#endif // MYVIDEOSTREAM_H
