struct win32_window_dimension
{
    int Width;
    int Height;
};

struct win32_offscreen_buffer
{
    // NOTE(tomi): Pixel memory order -> BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
    int BytesPerPixel;
};