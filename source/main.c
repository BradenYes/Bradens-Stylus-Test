#include <3ds.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	gfxInitDefault();

	PrintConsole topScreen, bottomScreen;

	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

    consoleSelect(&topScreen);
	printf("\x1b[16;17HBraden's Stylus Test");

	consoleSelect(&bottomScreen);
	printf("\x1b[1;0HTouch Screen Coords");

	while(aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break;

		touchPosition touch;

		hidTouchRead(&touch);

		consoleSelect(&bottomScreen);
		printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);

		gfxFlushBuffers();
		gfxSwapBuffers();


		gspWaitForVBlank();
	}

	gfxExit();
	return 0;

}