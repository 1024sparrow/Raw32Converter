#pragma once

// https://habr.com/ru/company/edison/blog/495614/
// Собиралось в Ubuntu-20.04 LTS. Там для сборки необходимо было доставить следующие пакеты:
// sudo apt install libavformat-dev
// sudo apt install libavfilter-dev
// sudo apt install libavdevice-dev

struct raw32converter_parameters
{
	const char *video;
	const char *output;
};

int raw32converter(struct raw32converter_parameters *a_parameters);
