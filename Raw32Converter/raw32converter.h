#pragma once

// "sudo apt install libavformat-dev" - lkjhlkjh lkjh
// sudo apt install libavfilter-dev
// sudo apt install libavdevice-dev

struct raw32converter_parameters
{
	const char *video;
	const char *output;
};

int raw32converter(struct raw32converter_parameters *a_parameters);
