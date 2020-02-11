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

#ifndef SPATIUMGL_GFX3D_COLOR_H
#define SPATIUMGL_GFX3D_COLOR_H

#include "spatiumglexport.hpp"

#include <array>  // std::array
#include <cmath>  // abs, fmod
#include <map>    // std::map
#include <vector> // std::vector

namespace spgl {

/// \class ColorT
/// \brief Color described by RGBA channels.
template<typename T>
struct SPATIUMGL_EXPORT ColorT
{
  T R; ///< Red
  T G; ///< Green
  T B; ///< Blue
  T A; ///< Alpha

  /// Construct RGB color from HSV.
  ///
  /// \param[in] hue Hue [0, 360]
  /// \param[in] saturation Saturation [0,1]
  /// \param[in] value Value [0,1]
  /// \param[in] alpha Alpha [0,1] (Passed)
  /// \return Color RGBA
  static ColorT<T> fromHsv(T hue, T saturation, T value, T alpha = 1)
  {
    T C = saturation * value;
    T X = C * (1 - abs(fmod(hue / 60.0, 2) - 1));
    T m = value - C;
    T Rs, Gs, Bs;

    if (hue >= 0 && hue < 60) {
      Rs = C;
      Gs = X;
      Bs = 0;
    } else if (hue >= 60 && hue < 120) {
      Rs = X;
      Gs = C;
      Bs = 0;
    } else if (hue >= 120 && hue < 180) {
      Rs = 0;
      Gs = C;
      Bs = X;
    } else if (hue >= 180 && hue < 240) {
      Rs = 0;
      Gs = X;
      Bs = C;
    } else if (hue >= 240 && hue < 300) {
      Rs = X;
      Gs = 0;
      Bs = C;
    } else {
      Rs = C;
      Gs = 0;
      Bs = X;
    }

    return { Rs + m, Gs + m, Bs + m, alpha };
  }

  /// Convert RGB color to HSV.
  ///
  /// \param[out] hue Hue [0, 360]
  /// \param[out] saturation Saturation [0,1]
  /// \param[out] value Value [0,1]
  /// \param[out] alpha Alpha [0,1] (Set to 1)
  void toHsv(T& hue, T& saturation, T& value) const
  {
    T Cmax = std::max(R, std::max(G, B));
    T Cmin = std::min(R, std::min(G, B));
    T delta = Cmax - Cmin;

    if (delta > 0) {
      if (Cmax == B) {
        hue = 60 * (((R - G) / delta) + 4);
      } else if (Cmax == G) {
        hue = 60 * (((B - R) / delta) + 2);
      } else if (Cmax == R) {
        hue = 60 * (fmod(((G - B) / delta), 6));
      }

      if (Cmax > 0) {
        saturation = delta / Cmax;
      } else {
        saturation = 0;
      }

      value = Cmax;
    } else {
      hue = 0;
      saturation = 0;
      value = Cmax;
    }
  }

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other color
  /// \return True if equal, false otherwise
  bool operator==(const ColorT<T>& other) const
  {
    if (this->R != other.R || this->G != other.G || this->B != other.B ||
        this->A != other.A) {
      return false;
    }
    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other color
  /// \return True if unequal, false otherwise
  bool operator!=(const ColorT<T>& other) const { return !(operator==(other)); }

  /// Get pointer to the underlying element storage.
  ///
  /// \return Pointer to underlying element storage.
  const T* data() const noexcept { return &R; }
};

using Color = ColorT<double>;

template<typename T>
struct SPATIUMGL_EXPORT ColorRampT
{
  /// Constructor.
  ///
  /// \param[in] minValue Minimal value
  /// \param[in] minColor Color at minimal value
  /// \param[in] maxValue Maximal value
  /// \param[in] maxColor Color at maximal value
  ColorRampT(T minValue, ColorT<T> minColor, T maxValue, ColorT<T> maxColor)
    : m_map()
  {
    m_map[minValue] = minColor;
    m_map[maxValue] = maxColor;
  }

  /// Construct grayscale color ramp.
  ///
  /// Black -> white
  ///
  /// \param[in] min Minimum value
  /// \param[in] max Maximum value
  /// \return Grayscale color ramp
  static ColorRampT<T> grayscale(T min, T max)
  {
    ColorRampT<T> ramp(min, { 0, 0, 0, 1 }, max, { 1, 1, 1, 1 });
    return ramp;
  }

  /// Construct RGB spectrum color ramp.
  ///
  /// Blue -> green -> red
  ///
  /// \param[in] min Minimum value
  /// \param[in] max Maximum value
  /// \return RGB spectrum color ramp
  static ColorRampT<T> spectral(T min, T max)
  {
    const T step = (max - min) / 2;
    ColorRampT<T> ramp(min, { 0, 0, 1, 1 }, max, { 1, 0, 0, 1 });
    ramp.addEntry(min + step, { 0, 1, 0, 1 });
    return ramp;
  }

  T min() const { return m_map.begin()->first; }

  T max() const { return m_map.rbegin()->first; }

  /// Add color entry.
  ///
  /// The value range is not expanded if the color is out of range. The color
  /// entry will then be ignored.
  ///
  /// \param[in] value Value [min,max]
  /// \param[in] color Color
  void addEntry(T value, const ColorT<T>& color)
  {
    if (value > min() && value < max()) {
      m_map[value] = color;
    }
  }

  /// Map value to color.
  ///
  /// This will perform interpolation to compute the color.
  ///
  /// \param[in] value Value [min,max]
  /// \returns Interpolated color
  ColorT<T> map(const T value) const
  {
    // Return color of min or max value if out of range of color ramp.
    const T minValue = min();
    const T maxValue = max();
    if (value <= minValue) {
      return m_map.at(minValue);
    } else if (value >= maxValue) {
      return m_map.at(maxValue);
    }

    // Determine two colors + weight to interpolate
    T valueLow;
    ColorT<T> colorLow;
    T valueHigh;
    ColorT<T> colorHigh;

    // Iterate color ramp
    bool hasHigher = false;
    for (auto it = m_map.begin(); it != m_map.end() && !hasHigher; ++it) {
      const T val = it->first;
      const ColorT<T> color = it->second;

      if (val <= value) {
        valueLow = val;
        colorLow = color;
      } else if (val > value) {
        valueHigh = val;
        colorHigh = color;
        hasHigher = true;
      }
    }

    // Colors to HSV
    T hsvHue1, hsvSaturation1, hsvValue1, alpha1 = colorLow.A;
    colorLow.toHsv(hsvHue1, hsvSaturation1, hsvValue1);
    T hsvHue2, hsvSaturation2, hsvValue2, alpha2 = colorHigh.A;
    colorHigh.toHsv(hsvHue2, hsvSaturation2, hsvValue2);

    // Interpolate colors
    const T weight1 = (valueHigh - value) / (valueHigh - valueLow);
    const T weight2 = (value - valueLow) / (valueHigh - valueLow);
    const T hsvHue = hsvHue1 * weight1 + hsvHue2 * weight2;
    const T hsvSaturation = hsvSaturation1 * weight1 + hsvSaturation2 * weight2;
    const T hsvValue = hsvValue1 * weight1 + hsvValue2 * weight2;
    const T alpha = alpha1 * weight1 + alpha2 * weight2;

    // Interpolated color to RGBA
    return ColorT<T>::fromHsv(hsvHue, hsvSaturation, hsvValue, alpha);
  }

  /// Convert to array of colors.
  ///
  /// \todo N must be >= 2
  ///
  /// \return array
  template<size_t N>
  std::array<ColorT<T>, N> toArray() const
  {
    std::array<ColorT<T>, N> array;
    const T maxValue = max();
    const T minValue = min();
    const T step = (maxValue - minValue) / (N - 1);
    for (size_t i = 0; i < N - 1; i++) {
      array[i] = map(minValue + i * step);
    }
    array[N - 1] = map(maxValue);
    return array;
  }

  /// Convert to std::vector of colors.
  ///
  /// \param[in] size Vector size (>=2)
  /// \return std::vector
  std::vector<ColorT<T>> toVector(size_t size) const
  {
    size = (size < 2 ? 2 : size);
    std::vector<ColorT<T>> vector;
    vector.reserve(size);
    const T maxValue = max();
    const T step = (maxValue - min()) / (size - 1);
    for (size_t i = 0; i < size - 1; i++) {
      vector.emplace_back(map(i * step));
    }
    vector.emplace_back(map(maxValue));
    return vector;
  }

private:
  std::map<T, ColorT<T>> m_map;
};

using ColorRamp = ColorRampT<double>;

} // namespace spgl

#endif // SPATIUMGL_GFX3D_COLOR_H
