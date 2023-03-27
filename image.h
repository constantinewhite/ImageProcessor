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

class Image {
public:
    struct Header {
        uint16_t signature;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t data_offset;
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

public:
    bool ReadFile(const std::string& file_name);

    bool WriteFile(const std::string& file_name);

    PixelMatrix& GetBody() {
        return body_;
    }

    uint32_t GetWidth() const {
        return header_.width;
    }

    uint32_t GetHeight() const {
        return header_.height;
    }

    void Resize(uint32_t new_width, uint32_t new_height) {
        header_.width = new_width;
        header_.height = new_height;
        header_.file_size = new_width * new_height * header_.bpp + header_.data_offset;
        header_.image_size = header_.width * header_.height;
    }

protected:
    bool ReadHeader(std::fstream& file);

    bool ReadBody(std::fstream& file);

    bool WriteHeader(std::fstream& file);

    bool WriteBody(std::fstream& file);

protected:
    Header header_;

    PixelMatrix body_;
};
