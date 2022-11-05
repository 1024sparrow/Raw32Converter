#include "raw32converter.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <stdio.h>

static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, char *filename)
{
	FILE *f;
	int i;
	f = fopen(filename,"w");
	// writing the minimal required header for a pgm file format
	// portable graymap format -> https://en.wikipedia.org/wiki/Netpbm_format#PGM_example
	fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);

	// writing line by line
	for (i = 0; i < ysize; i++)
		fwrite(buf + i * wrap, 1, xsize, f);
	fclose(f);
}

int raw32converter(struct raw32converter_parameters *a_parameters)
{
//	puts("not implemented");
//	return 0;

	AVFormatContext *pFormatContext = avformat_alloc_context();
	avformat_open_input(&pFormatContext, a_parameters->video, 0, 0);
	printf("Format %s, duration %lld us\n", pFormatContext->iformat->long_name, pFormatContext->duration);

	avformat_find_stream_info(pFormatContext, 0);
	AVStream
		*streamAudio = 0,
		*streamVideo = 0
	;
	for (int i = 0 ; i < pFormatContext->nb_streams ; ++i)
	{
		AVStream *stream = pFormatContext->streams[i];
		if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			streamAudio = stream;
		}
		else if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			printf("video codec name: %s\n", avcodec_get_name(stream->codec->codec_id));
			streamVideo = stream;
		}
//		AVCodecParameters *pLocalCodecParameters = stream->codecpar;
//		if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
//			printf("Video Codec: resolution %d x %d\n", pLocalCodecParameters->width, pLocalCodecParameters->height);
//		}
//		else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
//			printf("Audio Codec: %d channels, sample rate %d\n", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
//		}
	}

	if (streamAudio)
	{
		//
	}

	if (streamVideo)
	{
		const int
			width = streamVideo->codecpar->width,
			height = streamVideo->codecpar->height
		;
		AVCodec *codec = avcodec_find_decoder(streamVideo->codec->codec_id);
		if (avcodec_open2(streamVideo->codec, codec, 0) < 0)
		{
			puts("error 1");
			return 1;
		}



//		const AVCodec *pCodec = streamVideo->codec;
//		const AVCodecParameters *pCodecParameters;
//		AVCodecContext *pCodecContext = avcodec_alloc_context3(streamVideo->codec);
//		avcodec_parameters_to_context(pCodecContext, streamVideo->codecpar);
//		avcodec_open2(pCodecContext, streamVideo->codec, 0);

		AVPacket *pPacket = av_packet_alloc();
		AVFrame *pFrame = av_frame_alloc();

		int counter = 0;
		while(av_read_frame(pFormatContext, pPacket) >= 0)
//		while(av_read_frame(pFormatContext, pPacket) >= 0)
//		for (int i = 0 ; i < 5 ; ++i)//
		{
//			if (av_read_frame(pFormatContext, pPacket)<0)break;//


			if (pPacket->stream_index != streamVideo->index)
			{
				continue;
			}

			if (avcodec_send_packet(streamVideo->codec, pPacket))
			{
//				puts("2");
				continue;
			}
			avcodec_receive_frame(streamVideo->codec, pFrame);
			printf("frame w(%i) h(%i)\n", pFrame->width, pFrame->height);

			printf(
				"Frame %c (%d) pts %d dts %d key_frame %d [coded_picture_number %d, display_picture_number %d]\n",
				av_get_picture_type_char(pFrame->pict_type),
				streamVideo->codec->frame_number,
				pFrame->pts,
				pFrame->pkt_dts,
				pFrame->key_frame,
				pFrame->coded_picture_number,
				pFrame->display_picture_number
			);
			char buf[1024] = {'\0'};
			snprintf(buf, 1023, "123_%i", counter);
			save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, buf);

//			printf(
//				"Frame %c (%d) pts %d dts %d key_frame %d [coded_picture_number %d, display_picture_number %d]\n",
//				av_get_picture_type_char(pFrame->pict_type),
//				pCodecContext->frame_number,
//				pFrame->pts,
//				pFrame->pkt_dts,
//				pFrame->key_frame,
//				pFrame->coded_picture_number,
//				pFrame->display_picture_number
//			);
			++counter;
		}
	}

	return 0;
}































