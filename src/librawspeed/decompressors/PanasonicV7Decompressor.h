/*
    RawSpeed - RAW file decoder.

    Copyright (C) 2022 Jordan Neumeyer

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include "common/RawImage.h"                    // for RawImage
#include "decompressors/AbstractDecompressor.h" // for AbstractDecompressor
#include "io/ByteStream.h"                      // for ByteStream
#include <functional>

namespace rawspeed {

class PanasonicV7Decompressor final : public AbstractDecompressor {
  RawImage mRaw;

  ByteStream input;

  static constexpr int BytesPerBlock = 16;
  static constexpr int BitsPerSample = 14;
  static constexpr int PixelsPerBlock =
      (CHAR_BIT * BytesPerBlock) / BitsPerSample;

  inline void __attribute__((always_inline))
  // NOLINTNEXTLINE(bugprone-exception-escape): no exceptions will be thrown.
  decompressBlock(const ByteStream& block, int row, int col) const noexcept;

  // NOLINTNEXTLINE(bugprone-exception-escape): no exceptions will be thrown.
  void decompressRow(int row) const noexcept;

public:
  PanasonicV7Decompressor(const RawImage& img, const ByteStream& input_);

  void decompress() const;
};

} // namespace rawspeed
