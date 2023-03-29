#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

struct Pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

using Row = std::vector<Pixel>;

using PixelMatrix = std::vector<std::vector<Pixel>>;

class BitmapFileHeader {
public:
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
} __attribute__((packed));

class BitmapInfoHeader {
public:
    uint32_t dib_header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} __attribute__((packed));

class BitmapV5Header{
public:
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
    uint32_t alpha_mask;
    uint32_t cs_type;
    uint32_t endpoint_red_x;
    uint32_t endpoint_red_y;
    uint32_t endpoint_red_z;
    uint32_t endpoint_green_x;
    uint32_t endpoint_green_y;
    uint32_t endpoint_green_z;
    uint32_t endpoint_blue_x;
    uint32_t endpoint_blue_y;
    uint32_t endpoint_blue_z;
    uint32_t gamma_red;
    uint32_t gamma_green;
    uint32_t gamma_blue;
    uint32_t intent;
    uint32_t profile_data;
    uint32_t profile_size;
    uint32_t reserved;
} __attribute__((packed));


class Image {
public:
    bool ReadFile(const std::string& file_name);

    bool WriteFile(const std::string& file_name);

    PixelMatrix& GetBody() {
        return body_;
    }

    uint32_t GetWidth() const {
        return bitmap_info_header_.width;
    }

    uint32_t GetHeight() const {
        return bitmap_info_header_.height;
    }

    void Resize(uint32_t new_width, uint32_t new_height) {
        bitmap_info_header_.width = new_width;
        bitmap_info_header_.height = new_height;
        file_header_.file_size = new_width * new_height * bitmap_info_header_.bpp + file_header_.data_offset;
        bitmap_info_header_.image_size = bitmap_info_header_.width * bitmap_info_header_.height;
    }

protected:
    bool ReadFileHeader(std::fstream& file);

    bool ReadDibHeader(std::fstream& file);

    bool ReadBody(std::fstream& file);

    bool WriteFileHeader(std::fstream& file);

    bool WriteDibHeader(std::fstream& file);

    bool WriteBody(std::fstream& file);

protected:
    BitmapFileHeader file_header_;

    BitmapInfoHeader bitmap_info_header_;

    BitmapV5Header bitmap_v5_header_;

    PixelMatrix body_;
};
