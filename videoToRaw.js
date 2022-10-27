// nodejs module

// https://batchloaf.wordpress.com/2017/02/10/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg/
// https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/

const
	FS = require('fs'),
	CHILD_PROCESS = require('child_process')
;

module.exports = function(a_input, a_output){
	var
		res
	;
	res = CHILD_PROCESS.execSync(`/usr/bin/ffmpeg -i ${a_input} -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -`);
	console.log(res);
};
