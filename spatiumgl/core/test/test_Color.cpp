#include <gtest/gtest.h>

#include <spatiumgl/Color.hpp>

TEST(Color, constructor)
{
  const spgl::Color color{};
  EXPECT_EQ(color.R, 0);
  EXPECT_EQ(color.G, 0);
  EXPECT_EQ(color.B, 0);
  EXPECT_EQ(color.A, 0);
}

TEST(Color, aggregateInitialization)
{
  const spgl::Color color{ 1, 0.75, 0.5, 0.25 };
  EXPECT_EQ(color.R, 1);
  EXPECT_EQ(color.G, 0.75);
  EXPECT_EQ(color.B, 0.5);
  EXPECT_EQ(color.A, 0.25);
}

TEST(Color, compare)
{
  const spgl::Color color1{ 1, 0.75, 0.5, 0.25 };
  const spgl::Color color2{ 1, 0.75, 0.5, 0.25 };
  EXPECT_EQ(color1, color2);
}

TEST(Color, toFromHsv)
{
  const spgl::Color white{ 1, 1, 1, 1 };
  const std::array<double, 3> whiteHsv{ 0, 0, 1 };
  const spgl::Color black{ 0, 0, 0, 1 };
  const std::array<double, 3> blackHsv{ 0, 0, 0 };
  const spgl::Color gray{ 0.5, 0.5, 0.5, 1 };
  const std::array<double, 3> grayHsv{ 0, 0, 0.5 };
  const spgl::Color red{ 1, 0, 0, 1 };
  const std::array<double, 3> redHsv{ 0, 1, 1 };
  const spgl::Color orange{ 1, 0.5, 0, 1 };
  const std::array<double, 3> orangeHsv{ 30, 1, 1 };
  const spgl::Color yellow{ 1, 1, 0, 1 };
  const std::array<double, 3> yellowHsv{ 60, 1, 1 };
  const spgl::Color green{ 0, 1, 0, 1 };
  const std::array<double, 3> greenHsv{ 120, 1, 1 };
  const spgl::Color cyan{ 0, 1, 1, 1 };
  const std::array<double, 3> cyanHsv{ 180, 1, 1 };
  const spgl::Color blue{ 0, 0, 1, 1 };
  const std::array<double, 3> blueHsv{ 240, 1, 1 };
  const spgl::Color magenta{ 1, 0, 1, 1 };
  const std::array<double, 3> magentaHsv{ 300, 1, 1 };

  // White
  double hue, saturation, value;
  white.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, whiteHsv[0]);
  EXPECT_EQ(saturation, whiteHsv[1]);
  EXPECT_EQ(value, whiteHsv[2]);

  const spgl::Color white2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(white, white2);

  // Check black
  black.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, blackHsv[0]);
  EXPECT_EQ(saturation, blackHsv[1]);
  EXPECT_EQ(value, blackHsv[2]);

  const spgl::Color black2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(black, black2);

  // Check gray
  gray.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, grayHsv[0]);
  EXPECT_EQ(saturation, grayHsv[1]);
  EXPECT_EQ(value, grayHsv[2]);

  const spgl::Color gray2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(gray, gray2);

  // Check red
  red.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, redHsv[0]);
  EXPECT_EQ(saturation, redHsv[1]);
  EXPECT_EQ(value, redHsv[2]);

  const spgl::Color red2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(red, red2);

  // Check orange
  orange.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, orangeHsv[0]);
  EXPECT_EQ(saturation, orangeHsv[1]);
  EXPECT_EQ(value, orangeHsv[2]);

  const spgl::Color orange2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(orange, orange2);

  // Check yellow
  yellow.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, yellowHsv[0]);
  EXPECT_EQ(saturation, yellowHsv[1]);
  EXPECT_EQ(value, yellowHsv[2]);

  const spgl::Color yellow2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(yellow, yellow2);

  // Check green
  green.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, greenHsv[0]);
  EXPECT_EQ(saturation, greenHsv[1]);
  EXPECT_EQ(value, greenHsv[2]);

  const spgl::Color green2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(green, green2);

  // Check cyan
  cyan.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, cyanHsv[0]);
  EXPECT_EQ(saturation, cyanHsv[1]);
  EXPECT_EQ(value, cyanHsv[2]);

  const spgl::Color cyan2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(cyan, cyan2);

  // Check blue
  blue.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, blueHsv[0]);
  EXPECT_EQ(saturation, blueHsv[1]);
  EXPECT_EQ(value, blueHsv[2]);

  const spgl::Color blue2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(blue, blue2);

  // Check magenta
  magenta.toHsv(hue, saturation, value);
  EXPECT_EQ(hue, magentaHsv[0]);
  EXPECT_EQ(saturation, magentaHsv[1]);
  EXPECT_EQ(value, magentaHsv[2]);

  const spgl::Color magenta2 = spgl::Color::fromHsv(hue, saturation, value);
  EXPECT_EQ(magenta, magenta2);
}

TEST(ColorRamp, constructor)
{
  const double minValue = 0;
  const spgl::Color minColor = { 0, 0, 0, 1 };
  const double maxValue = 1;
  const spgl::Color maxColor = { 1, 1, 1, 1 };
  const spgl::ColorRamp ramp(minValue, minColor, maxValue, maxColor);
  EXPECT_EQ(ramp.min(), minValue);
  EXPECT_EQ(ramp.map(minValue), minColor);
  EXPECT_EQ(ramp.max(), maxValue);
  EXPECT_EQ(ramp.map(maxValue), maxColor);
}

TEST(ColorRamp, map)
{
  spgl::ColorRamp grayscale = spgl::ColorRamp::grayscale(0, 4);
  spgl::Color black = grayscale.map(0);
  EXPECT_EQ(black, (spgl::Color{ 0, 0, 0, 1 }));
  spgl::Color lightGray = grayscale.map(1);
  EXPECT_EQ(lightGray, (spgl::Color{ 0.25, 0.25, 0.25, 1 }));
  spgl::Color gray = grayscale.map(2);
  EXPECT_EQ(gray, (spgl::Color{ 0.5, 0.5, 0.5, 1 }));
  spgl::Color darkGray = grayscale.map(3);
  EXPECT_EQ(darkGray, (spgl::Color{ 0.75, 0.75, 0.75, 1 }));
  spgl::Color white = grayscale.map(4);
  EXPECT_EQ(white, (spgl::Color{ 1, 1, 1, 1 }));

  spgl::Color blackOutOfRange = grayscale.map(-1);
  EXPECT_EQ(blackOutOfRange, (spgl::Color{ 0, 0, 0, 1 }));
  spgl::Color whiteOutOfRange = grayscale.map(5);
  EXPECT_EQ(whiteOutOfRange, (spgl::Color{ 1, 1, 1, 1 }));
}

TEST(ColorRamp, toArray)
{
  spgl::ColorRamp spectral = spgl::ColorRamp::spectral(0, 5);
  std::array<spgl::Color, 6> arr = spectral.toArray<6>();
  EXPECT_EQ(arr[0], (spgl::Color{ 1, 0, 0, 1 }));
  EXPECT_EQ(arr[1], (spgl::Color{ 1, 0.5, 0, 1}));
  EXPECT_EQ(arr[2], (spgl::Color{ 1, 1, 0, 1 }));
  EXPECT_EQ(arr[3], (spgl::Color{ 0, 1, 0, 1 }));
  EXPECT_EQ(arr[4], (spgl::Color{ 0, 1, 1, 1 }));
  EXPECT_EQ(arr[5], (spgl::Color{ 0, 0, 1, 1 }));
}

TEST(ColorRamp, toVector)
{
  spgl::ColorRamp spectral = spgl::ColorRamp::spectral(0, 5);
  std::vector<spgl::Color> vec = spectral.toVector(6);
  EXPECT_EQ(vec[0], (spgl::Color{ 1, 0, 0, 1 }));
  EXPECT_EQ(vec[1], (spgl::Color{ 1, 0.5, 0, 1}));
  EXPECT_EQ(vec[2], (spgl::Color{ 1, 1, 0, 1 }));
  EXPECT_EQ(vec[3], (spgl::Color{ 0, 1, 0, 1 }));
  EXPECT_EQ(vec[4], (spgl::Color{ 0, 1, 1, 1 }));
  EXPECT_EQ(vec[5], (spgl::Color{ 0, 0, 1, 1 }));
}
