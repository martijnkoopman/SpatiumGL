/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_IMAGE_H
#define SPATIUMGL_IMAGE_H

#include "Vector.hpp"

namespace spatiumgl {

/// \class ImageColumn
template<typename T = unsigned char, size_t N = 3>
class ImageColumn
{
public:
  ImageColumn()
    : m_height(1)
    , m_rows(new Vector<T, N>[1])
  {
    // m_rows[0] = 0;
  }

  /// Constructor
  ///
  /// \param[in] height Image column height in pixels
  /// \throw std::bad_alloc on bad allocation
  ImageColumn(size_t height)
    : m_height(height)
    , m_rows(new Vector<T, N>[height])
  {
    // Clear values
    // clear();
  }

  // Destructor
  ~ImageColumn() { delete[] m_rows; }

  Vector<T, N>& operator[](size_t row) { return m_rows[row]; }

  const Vector<T, N>& operator[](size_t row) const { return m_rows[row]; }

  constexpr size_t height() const { return m_height; }

protected:
  size_t m_height;
  Vector<T, N>* m_rows;
};

/// \class Image
/// \brief Templated image container
///
/// An image has no knowledge about color. The minimum image size is 1x1 pixel.
template<typename T = unsigned char, size_t N = 3>
class Image
{
public:
  /// Constructor
  /// Constructs an image with a single pixel to ensure function pixel() can
  /// always return a reference to a value.
  ///
  /// \throw std::bad_alloc on bad allocation
  Image()
    : m_width(1)
    , m_height(1)
    , m_columns(new ImageColumn<T, N>[1])
  {
    // Clear value
    m_imageData[0] = { 0 };
  }

  /// Constructor
  ///
  /// \param[in] width Image width in pixels
  /// \param[in] height Image height in pixels
  /// \throw std::bad_alloc on bad allocation
  Image(size_t width, size_t height)
    : m_width(width)
    , m_height(height)
    , m_columns(new ImageColumn<T, N>[width])
  {
    // Clear values
    // clear();
  }

  // Destructor
  ~Image() { delete[] m_columns; }

  ImageColumn<T, N>& operator[](size_t col) { return m_columns[col]; }

  const ImageColumn<T, N>& operator[](size_t col) const
  {
    return m_columns[col];
  }

  constexpr size_t width() const { return m_width; }

  constexpr size_t height() const { return m_height; }

  constexpr size_t channels() const { return N; }

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os, const Image<T, N>& image)
  {
    os << "(" << image.width() << ", " << image.width() << ", "
       << image.channels() << ")";
    return os;
  }

protected:
  size_t m_width;
  size_t m_height;
  ImageColumn<T, N>* m_columns;
};
} // namespace spatium

#endif // SPATIUMGL_IMAGE_H