#include "raw32converter.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <stdio.h>

int raw32converter(struct raw32converter_parameters &a_parameters)
{
//	puts("not implemented");
//	return 0;

	AVFormatContext *pFormatContext = avformat_alloc_context();
	//avformat_open_input(&pFormatContext, a_parameters.video, nullptr, nullptr);
	avformat_open_input(&pFormatContext, "a_parameters.video", nullptr, nullptr);
//	printf("Format %s, duration %lld us", pFormatContext->iformat->long_name, pFormatContext->duration);

	return 0;
}
