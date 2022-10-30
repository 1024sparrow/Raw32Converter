//#include <QCoreApplication>
#include <string.h>
#include <stdio.h>

#include "raw32converter.h"

int main(int argc, char **argv)
{
	for (int iArg = 0 ; iArg < argc ; ++iArg)
	{
		char *arg = argv[iArg];
		if (!strcmp(arg, "--help"))
		{
			puts(R"(
Программа Raw32Converter - конвертер видеофайлов в raw32-формат

Raw32Converter --video <путь_до_видеофайла> --output <в_какой_файл_записать_raw32>
)");
			return 0;
		}
	}
	int
		bArgVideo = 0,
		bArgOutput = 0
	;
	enum
	{
		stateInitial,
		stateVideo,
		stateOutput,
		stateReady
	} state = stateInitial;

	struct raw32converter_parameters parameters;
	memset(&parameters, 0, sizeof(parameters));
	for (int iArg = 1 ; iArg < argc ; ++iArg)
	{
		char *arg = argv[iArg];
		if (state == stateInitial)
		{
			if (!strcmp(arg, "--video"))
			{
				if (bArgVideo)
				{
					puts("пресечена попытка повторной установки значения аргумента \"--video\"");
					return 1;
				}
				bArgVideo = 1;
				state = stateVideo;
			}
			else if (!strcmp(arg, "--output"))
			{
				if (bArgOutput)
				{
					puts("пресечена попытка повторной установки значения аргумента \"--output\"");
					return 1;
				}
				bArgOutput = 1;
				state = stateOutput;
			}
			else if (!strncmp(arg, "-", 1))
			{
				printf("Ключ \"%s\" не поддерживается\n", arg);
				return 1;
			}
			else
			{
				printf("Неожиданный аргумент: \"%s\"\n", arg);
				return 1;
			}
		}
		else if (state == stateVideo)
		{
			if (!strncmp(arg, "-", 1))
			{
				printf("Ключ \"%s\": значение аргумента \"--video\" ожидается\n", arg);
				return 1;
			}
			else
			{
				parameters.video = arg;
				state = bArgOutput ? stateReady : stateInitial;
			}
		}
		else if (state == stateOutput)
		{
			if (!strncmp(arg, "-", 1))
			{
				printf("Ключ \"%s\": значение аргумента \"--output\" ожидается\n", arg);
				return 1;
			}
			else
			{
				parameters.output = arg;
				state = bArgVideo ? stateReady : stateInitial;
			}
		}
		else if (state == stateReady)
		{
			if (!strncmp(arg, "-", 1))
			{
				printf("Ключ \"%s\" не поддерживается\n", arg);
				return 1;
			}
			else
			{
				printf("Неожиданный аргумент: \"%s\"\n", arg);
				return 1;
			}
		}
	}
	if (state != stateReady)
	{
		const char *arg = "??";
		if (state == stateVideo)
		{
			puts("Ключ \"--video\": значение аргумента ожидается");
		}
		else if (state == stateOutput)
		{
			puts("Ключ \"--output\": значение аргумента ожидается");
		}
		else if (state == stateInitial)
		{
			if (bArgVideo)
			{
				if (!bArgOutput)
				{
					puts("Не указан обязательный аргумент \"--output\"");
				}
			}
			else
			{
				puts("Не указан режим. Необходимо указать параметр \"--video\"");
			}
		}
		else
		{
			puts("Ошибка парсинга аргументов командной строки");
		}
		return 1;
	}

	// Проверка полноты задания аргументов уже произведена.
	if (bArgVideo)
	{
			if (raw32converter(&parameters))
			{
				return 1;
			}
			return 0;
	}
	puts("Не указан режим. Необходимо указать параметр \"--video\"");
	return 1;
}
