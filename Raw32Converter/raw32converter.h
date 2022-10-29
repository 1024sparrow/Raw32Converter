#pragma once

struct raw32converter_parameters
{
	const char *video {nullptr};
	const char *output {nullptr};
};

int raw32converter(struct raw32converter_parameters &a_parameters);
