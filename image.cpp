#include "image.h"

#include <stdexcept>
#include <fstream>

int const VALUES_IN_BYTE = 32;
int const PAD_ROW = 4;
int const SIGN = 0x4D42;
int const BITMAP_INFO_HEADER_SIZE = 40;
int const BITMAP_V5_HEADER_SIZE = 124;
int const BPP = 24;

bool Image::ReadFile(const std::string& file_name) {
    if (file_name.empty()) {
        throw std::logic_error("Filename not provided");
    }

    std::fstream file(file_name, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    if (!ReadFileHeader(file)) {
        return false;
    }
    if (!ReadDibHeader(file)) {
        return false;
    }
    if (!ReadBody(file)) {
        return false;
    }
    return true;
}

bool Image::ReadFileHeader(std::fstream &file) {
    file.read(reinterpret_cast<char *>(&file_header_), sizeof(BitmapFileHeader));
    if (file_header_.signature != SIGN) {
        return false;
    }
    return true;
}

bool Image::ReadDibHeader(std::fstream &file) {
    file.read(reinterpret_cast<char *>(&bitmap_info_header_), sizeof(BitmapInfoHeader));
    if (bitmap_info_header_.dib_header_size == BITMAP_V5_HEADER_SIZE) {
        file.read(reinterpret_cast<char *>(&bitmap_v5_header_), sizeof(BitmapV5Header));
    } else if (bitmap_info_header_.dib_header_size != BITMAP_INFO_HEADER_SIZE) {
        return false;
    }
    if (bitmap_info_header_.bpp != BPP) {
        return false;
    }
    return true;
}

bool Image::ReadBody(std::fstream &file) {
    body_.resize(bitmap_info_header_.height);
    uint32_t row_size = ((bitmap_info_header_.width * bitmap_info_header_.bpp + VALUES_IN_BYTE - 1) / VALUES_IN_BYTE) * 4;
    std::vector<char> row_buffer(row_size);
    for (int i = 0; i < bitmap_info_header_.height; ++i) {
        if (!file.read(row_buffer.data(), row_size)) {
            return false;
        }
        body_[i].resize(bitmap_info_header_.width);
        for (int j = 0; j < bitmap_info_header_.width; ++j) {
            Pixel &pixel = body_[i][j];
            pixel.b = row_buffer[j * 3];
            pixel.g = row_buffer[j * 3 + 1];
            pixel.r = row_buffer[j * 3 + 2];
        }
    }
    return true;
}

bool Image::WriteFile(const std::string& file_name) {
    if (file_name.empty()) {
        throw std::logic_error("Filename not provided");
    }

    std::fstream file(file_name, std::ios_base::out | std::ios_base::binary);

    if (!file.is_open()) {
        return false;
    }
    if (!WriteFileHeader(file)) {
        return false;
    }
    if (!WriteDibHeader(file)) {
        return false;
    }
    if (!WriteBody(file)) {
        return false;
    }
    return true;
}

bool Image::WriteFileHeader(std::fstream &file) {
    if (!file.write(reinterpret_cast<char *>(&file_header_), sizeof(file_header_))) {
        return false;
    }
    return true;
}

bool Image::WriteDibHeader(std::fstream &file) {
    if (!file.write(reinterpret_cast<char *>(&bitmap_info_header_), sizeof(bitmap_info_header_))) {
        return false;
    }
    if (bitmap_info_header_.dib_header_size == BITMAP_V5_HEADER_SIZE) {
        if (!file.write(reinterpret_cast<char *>(&bitmap_v5_header_), sizeof(BitmapV5Header))) {
            return false;
        }
    }
    return true;
}

bool Image::WriteBody(std::fstream &file) {
    uint32_t row_size = ((bitmap_info_header_.width * bitmap_info_header_.bpp + VALUES_IN_BYTE - 1) / VALUES_IN_BYTE) * PAD_ROW;
    std::vector<char> row_buffer(row_size);
    for (int i = 0; i < bitmap_info_header_.height; ++i) {
        for (int j = 0; j < bitmap_info_header_.width; ++j) {
            const Pixel &pixel = body_[i][j];
            row_buffer[j * sizeof(Pixel)] = static_cast<char>(pixel.b);
            row_buffer[j * sizeof(Pixel) + 1] = static_cast<char>(pixel.g);
            row_buffer[j * sizeof(Pixel) + 2] = static_cast<char>(pixel.r);
        }
        if (!file.write(row_buffer.data(), row_size)) {
            return false;
        }
    }
    return true;
}
