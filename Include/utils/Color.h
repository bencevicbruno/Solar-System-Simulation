#pragma once

class Color
{
public:
	float r, g, b, a;

	static Color CreateFromRGB(int r, int g, int b);
	static Color CreateFromRGBA(int r, int g, int b, int a);

	static Color CreateRandom();
	static Color CreateRandomGray(float minBrightness, float maxBrightness);

private:
	Color(float r, float g, float b, float a);
};

