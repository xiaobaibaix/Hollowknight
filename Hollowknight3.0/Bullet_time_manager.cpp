#include "Bullet_time_manager.h"
#include "util.h"

#include <graphics.h>

Bullet_time_manager::Bullet_time_manager()
{
}

Bullet_time_manager::~Bullet_time_manager()
{
}


void Bullet_time_manager::post_process()
{
    DWORD* buffer = GetImageBuffer();
    int w = getwidth();
    int h = getheight();
    for (int y = 0; y < h;y++) {
        for (int x = 0; x < w;x++) {
            int idx = y * w + x;
            DWORD color = buffer[idx];
            BYTE r = (BYTE)(GetBValue(color) * lerp(1.f, DST_COLOR_FACTOR, process));
            BYTE g = (BYTE)(GetGValue(color) * lerp(1.f, DST_COLOR_FACTOR, process));
            BYTE b = (BYTE)(GetRValue(color) * lerp(1.f, DST_COLOR_FACTOR, process));
            buffer[idx] = BGR(RGB(r, g, b)) | (((DWORD)(BYTE)(255)) << 24);
        }
    }
}

void Bullet_time_manager::set_status(Status status)
{
    this->status = status;
}

float Bullet_time_manager::on_update(float delta)
{
    float delta_process = SPEED_PROCESS * delta;
    process += delta_process * (status == Status::Entering ? 1 : -1);

    if (process < 0)process = 0;
    if (process > 1.0f)process = 1.0f;

    return delta*lerp(1.f,DST_DELTA_FACTOR,process);
}

