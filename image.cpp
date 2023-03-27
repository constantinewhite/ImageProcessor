#include "image.h"

#include <stdexcept>
#include <fstream>

int const BITS_IN_BYTE = 32;
int const PAD_ROW = 4;
int const SIGN = 0x4D42;
int const DIB_HEADER_SIZE = 40;
int const BPP = 24;

bool Image::ReadFile(const std::string& file_name) {
    if (file_name.empty()) {
        throw std::logic_error("Filename not provided");
    }

    std::fstream file(file_name, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    if (!ReadHeader(file)) {
        return false;
    }
    if (!ReadBody(file)) {
        return false;
    }
    return true;
}

bool Image::ReadHeader(std::fstream &file) {
    file.read(reinterpret_cast<char *>(&header_), sizeof(Header));
    if (header_.signature != SIGN) {
        return false;
    }
    if (header_.dib_header_size != DIB_HEADER_SIZE) {
        return false;
    }
    if (header_.bpp != BPP) {
        return false;
    }
    return true;
}

bool Image::ReadBody(std::fstream &file) {
    body_.resize(header_.height);
    uint32_t row_size = ((header_.width * header_.bpp + BITS_IN_BYTE - 1) / BITS_IN_BYTE) * 4;
    std::vector<char> row_buffer(row_size);
    for (int i = 0; i < header_.height; ++i) {
        if (!file.read(row_buffer.data(), row_size)) {
            return false;
        }
        body_[i].resize(header_.width);
        for (int j = 0; j < header_.width; ++j) {
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

    if (!WriteHeader(file)) {
        return false;
    }
    if (!WriteBody(file)) {
        return false;
    }
    return true;
}

bool Image::WriteHeader(std::fstream &file) {
    if (!file.write(reinterpret_cast<char *>(&header_), sizeof(header_))) {
        return false;
    }
    return true;
}

bool Image::WriteBody(std::fstream &file) {
    uint32_t row_size = ((header_.width * header_.bpp + BITS_IN_BYTE - 1) / BITS_IN_BYTE) * PAD_ROW;
    std::vector<char> row_buffer(row_size);
    for (int i = 0; i < header_.height; ++i) {
        for (int j = 0; j < header_.width; ++j) {
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
