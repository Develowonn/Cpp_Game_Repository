/*
	변수명 규칙

	int 타입   : 접두사 n
	float 타입 : 접두사 f
*/

#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class PerlinNoise : public olc::PixelGameEngine
{
public:
	PerlinNoise() {
		sAppName = "PerlinNoise Program";
	}
private:
	// 2D Noise variables
	float* fNoiseSeed2D = nullptr; // 노이즈 시드 값
	float* fPerlinNoise2D = nullptr; // PerlinNoise 값 저장 
	int    nOutputWidth = 256;     // 출력될 데이터 크기
	int    nOutputHeight = 256;

	// 1D Noise variables
	float* fNoiseSeed1D   = nullptr; // 노이즈 시드 값
	float* fPerlinNoise1D = nullptr; // PerlinNoise 값 저장 
	int    nOutputSize = 256;     // 출력될 데이터 크기

	// ETC
	int    nOctaveCount = 1;
	int    nMode = 1;
	float  fScalingBias = 2.0f;

	// Unity Start() 함수 같은 것
	bool OnUserCreate() override {
		// 1D Noise Variable Init
		nOutputSize = ScreenWidth();
		fNoiseSeed1D = new float[nOutputSize];
		fPerlinNoise1D = new float[nOutputSize];

		for (int i = 0; i < nOutputSize; i++)
			fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;

		// 2D Noise Vairable Init
		nOutputWidth = ScreenWidth();
		nOutputHeight = ScreenHeight();
		fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
		fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];

		for (int i = 0; i < nOutputWidth * nOutputHeight; i++)
			fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
		return true;
	}

	// Unity Update() 함수 같은 것
	bool OnUserUpdate(float fElapsedTime) override {
		if (GetKey(olc::SPACE).bReleased) {
			Clear(olc::BLACK);
			nOctaveCount++;
		}

		if (nOctaveCount == 7) {
			Clear(olc::BLACK);
			nOctaveCount = 1;
		}

		if (GetKey(olc::Z).bReleased) {
			for (int i = 0; i < nOutputSize; i++) fNoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;
			Clear(olc::BLACK);
		}

		if (GetKey(olc::Q).bReleased) {
			Clear(olc::BLACK);
			fScalingBias += 0.2f;
		}

		if (GetKey(olc::A).bReleased) {
			Clear(olc::BLACK);
			fScalingBias -= 0.2f;
		}

		if (fScalingBias < 0.2) {
			Clear(olc::BLACK);
			fScalingBias = 0.2f;
		}

		if (GetKey(olc::K1).bReleased)
			nMode = 1;

		if (GetKey(olc::K2).bReleased)
			nMode = 2;

		if (GetKey(olc::K3).bReleased)
			Clear(olc::BLACK);

		if (nMode == 1) {
			PerlinNoise1D(nOutputSize, fNoiseSeed1D, nOctaveCount, fScalingBias, fPerlinNoise1D);

			for (int x = 0; x < nOutputSize; x++) {
				int y = -(fPerlinNoise1D[x] * (float)ScreenHeight() / 2.0f) + (float)ScreenHeight() / 2.0f;
				for (int f = y; f < ScreenHeight() / 2; f++) {
					Draw(x, f, olc::GREEN);
				}
			}
			DrawStringDecal({ 0, 8 }, "Seed: " + std::to_string(*fNoiseSeed1D), olc::RED, { 0.5f, 0.5f });
		}

		if (nMode == 2) {
			if (GetKey(olc::Z).bReleased) // Noise Between 0 and +1
				for (int i = 0; i < nOutputWidth * nOutputHeight; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;

			PerlinNoise2D(nOutputWidth, nOutputHeight, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);

			for (int x = 0; x < nOutputWidth; x++) {
				for (int y = 0; y < nOutputHeight; y++) {
					olc::Pixel bg_col, fg_col;
					int pixel_bw = (int)(fPerlinNoise2D[y * nOutputWidth + x] * 16.0f);
					switch (pixel_bw)
					{
					case 0: bg_col = olc::DARK_BLUE; break;

					case 1: bg_col = olc::DARK_BLUE; break;
					case 2: bg_col = olc::DARK_BLUE; break;
					case 3: bg_col = olc::DARK_BLUE; break;
					case 4: bg_col = olc::DARK_BLUE; break;

					case 5: bg_col = olc::BLUE; break;
					case 6: bg_col = olc::BLUE; break;
					case 7: bg_col = olc::BLUE; break;
					case 8: bg_col = olc::BLUE; break;

					case 9:  bg_col = olc::GREEN; break;
					case 10: bg_col = olc::GREEN; break;
					case 11: bg_col = olc::GREEN; break;
					case 12: bg_col = olc::GREEN; break;

					case 13: bg_col = olc::DARK_GREY; break;
					case 14: bg_col = olc::DARK_GREY; break;
					case 15: bg_col = olc::DARK_GREY; break;
					case 16: bg_col = olc::DARK_GREY; break;
					}

					Draw(x, y, bg_col);
				}
				DrawStringDecal({ 0, 8 }, "Seed: " + std::to_string(*fNoiseSeed2D), olc::RED, { 0.5f, 0.5f });
			}
		}

		DrawStringDecal({ 0, 2 }, "Octaves: " + std::to_string(nOctaveCount), olc::RED, { 0.5f, 0.5f });


		return true;
	}

	void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput) {
		// Used 2D Perlin Noise 
		for (int x = 0; x < nWidth; x++)
			for (int y = 0; y < nHeight; y++) {
				float fNoise = 0.0f;
				float fScale = 1.0f;
				float fScaleAcc = 0.0f;

				for (int o = 0; o < nOctaves; o++) {
					int nPitch = nWidth >> o;
					int nSampleX1 = (x / nPitch) * nPitch;
					int nSampleY1 = (y / nPitch) * nPitch;

					int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
					int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

					float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
					float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

					float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
					float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

					fScaleAcc += fScale;
					fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
					fScale = fScale / fBias;
				}

				fOutput[y * nWidth + x] = fNoise / fScaleAcc;
			}
	}

	void PerlinNoise1D(int nCount, float* fSeed, int nOctaves, float fBias, float* fOutput) {
		// Used 1D Perlin Noise 
		for (int x = 0; x < nCount; x++) {
			float fNoise = 0.0f;
			float fScale = 1.0f;
			float fScaleAcc = 0.0f;

			for (int o = 0; o < nOctaves; o++) {
				int nPitch = nCount >> o;
				int nSample1 = (x / nPitch) * nPitch;
				int nSample2 = (nSample1 + nPitch) % nCount;

				float fBlend = (float)(x - nSample1) / (float)nPitch;
				float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

				fNoise += fSample * fScale;
				fScaleAcc += fScale;
				fScale = fScale / fBias;
			}
			fOutput[x] = fNoise / fScaleAcc;
		}
	}
};

int main()
{
	PerlinNoise game;
	if (game.Construct(500, 256, 3, 3)) {
		game.Start();
	}

	return 0;
}
