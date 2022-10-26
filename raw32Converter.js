#!/usr/bin/node

var
	state = 'stateInitial',
	args = {
		video: '',
		output: ''
	}
;

for (const oArg of process.argv.slice(2)){
	if (oArg === '--help'){
		process.stdout.write(`Программа Raw32Converter - конвертер видеофайлов в raw32-формат

Raw32Converter --video <путь_до_видеофайла> --output <в_какой_файл_записать_raw32>
`);
		process.exit(0);
	}
}

function ERROR(a_descr){
	process.stderr.write(a_descr + '\n');
	process.exit(1);
}

for (const oArg of process.argv.slice(2)){
	//console.log(`state("${state}") arg("${oArg}")`);//
	if (state === 'stateInitial'){
		if (oArg.slice(0, 2) === '--' && args.hasOwnProperty(oArg.slice(2))){
			const name = oArg.slice(2)[0].toUpperCase() + oArg.slice(2).slice(1);
			if (args[`bArg${name}`]){
				ERROR(`пресечена попытка повторной установки значения аргумента "${oArg}"`);
			}
			args[`bArg${name}`] = true;
			state = `state${name}`;
		}
		else if (oArg[0] === '-'){
			ERROR(`неподдерживаемый ключ: "${oArg}"`);
		}
		else{
			ERROR(`неожиданный аргумент: "${oArg}"`);
		}
	}
	else {
		for (const i in args){
			const name = i[0].toUpperCase() + i.slice(1);
			if (state === `state${name}`){
				if (oArg[0] === '-'){
					ERROR(`ключ "${oArg}": ожидается значение аргумента`);
				}
				else{
					args[i] = oArg;
					state = 'stateInitial';
				}
			}
		}
	}
}

for (const i in args){
	const name = i[0].toUpperCase() + i.slice(1);
	if (state === `state${name}`){
		ERROR(`Аргумент "--${i}": не указано значение`);
	}
}

//console.log(JSON.stringify(args, undefined, 4));//

if (args.bArgVideo){
	if (!args.bArgOutput){
		ERROR('Не указан обязательный аргумент "--output"');
	}
	(function(a_video, a_output){
		// https://batchloaf.wordpress.com/2017/02/10/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg/
		// https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
	})(args.video, args.output);
}
else {
	ERROR('Не указан режим. Необходимо указать параметр "--video"');
}
