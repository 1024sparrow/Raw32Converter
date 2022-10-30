#include "raw32converter.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <stdio.h>

int raw32converter(struct raw32converter_parameters *a_parameters)
{
//	puts("not implemented");
//	return 0;

	AVFormatContext *pFormatContext = avformat_alloc_context();
	avformat_open_input(&pFormatContext, a_parameters->video, 0, 0);
	printf("Format %s, duration %lld us\n", pFormatContext->iformat->long_name, pFormatContext->duration);

	avformat_find_stream_info(pFormatContext, 0);
	for (int i = 0 ; i < pFormatContext->nb_streams ; ++i)
	{
		//
	}

	return 0;
}
