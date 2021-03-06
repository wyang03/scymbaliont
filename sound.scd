SerialPort.listDevices;  //to get a list of all available Serial Port devices
SerialPort.closeAll;  // to close all serial port
~port = SerialPort("/dev/tty.usbserial-DN04QVFW", 9600);  //select the xbee port to be used for serial communication

// read and partition the ldr sensor data
(
~charArray = [];
~readValue = Routine({
	var ascii;
	{
		ascii = ~port.read.asAscii;

		case
		{ascii==nil}{nil}
		{ascii.isDecDigit}{~charArray=~charArray.add(ascii.digit)}
		{ascii==$a}{~ldr0Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$b}{~ldr1Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$c}{~ldr2Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$d}{~ldr3Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$e}{~ldr4Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$f}{~ldr5Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$g}{~ldr6Val = ~charArray.convertDigits; ~charArray = []}	
		{ascii==$h}{~ldr7Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$i}{~ldr8Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$j}{~ldr9Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$k}{~ldr10Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$l}{~ldr11Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$m}{~ldr12Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$n}{~ldr13Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$o}{~ldr14Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$p}{~ldr15Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$q}{~ldr16Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$r}{~ldr17Val = ~charArray.convertDigits; ~charArray = []}
		{ascii==$s}{~ldr18Val = ~charArray.convertDigits; ~charArray = [ ]}
		{ascii==$t}{~ldr19Val = ~charArray.convertDigits; ~charArray = []}



		{true}{nil};

		[~ldr0Val, ~ldr1Val, ~ldr2Val, ~ldr3Val, ~ldr4Val].postln;
	}.loop
}).play
)

~readValue.stop;  // to stop reading data

(
// sample buffers
a = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/40_ss/7/var1/0.wav").load;  //crackle
b = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/40_ss/9/var_1_Pulse_Ring_Mod/0.wav").load;//rhythmic click
c = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/32_t_insects/4.wav").load;//water
d = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/40_ss/12_organ/3.wav").load; //bell-distance
e = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/28_chorus_chant/2/3.wav").load; //chant
f = CtkBuffer.playbuf("/Volumes/weiyang/voice_project/Sounds/08_bubble/6.wav").load; //bubble
)

//binaural decoder
~decoder = FoaDecoderKernel.newCIPIC;

//playback synthdef with bandpass filter and foa focus
(
~synth1 = CtkSynthDef(\plb, {|rate=1, gain=0.5, buffer=0, bpfFreq=440, rq=1.0, rotAngle=0.0, theta = 0.0, gate=1, delayTime= 0.1|
	var env, sig, out, amp;
	amp = gain.dbamp;
	sig = PlayBuf.ar(4, buffer, BufRateScale.kr(buffer)*rate.lag(0.1), loop: 1);
	env = EnvGen.kr(Env.adsr(Rand(3, 10), Rand(10, 20), releaseTime: Rand(10, 20)), gate);
	sig = BPF.ar(sig, bpfFreq.lag(0.1), rq);
	// if(bpf==0, {sig = BPF.ar(sig, bpfFreq, rq)},{ sig});
	sig = FoaRotate.ar(sig, rotAngle);
	sig = FoaFocus.ar(sig, pi/3, theta);
	out  = FoaDecode.ar(sig, ~decoder);
	out = DelayN.ar(out, 0.2, SinOsc.ar(0.2, 0, delayTime, delayTime), mul: 0.5, add: out);
	Out.ar(0, out *1.618* amp.lag(0.1) * env);
})


~synth3 = CtkSynthDef('help-dynKlang', { |outBus=0, amp = 0.1, gate=0, oscfreq=0.5,
	freqs=#[220, 440, 880, 1760],
	amps=#[0.35, 0.23, 0.12, 0.05],
	phases=#[1, 1.5, 2, 2.5]|
	var sig, env;
	sig = DynKlang.ar(`[freqs, amps, phases]);
	sig = sig * SinOsc.ar(LFNoise2.ar(oscfreq).range(1, 5)).dup;
	env = EnvGen.ar(Env.adsr(Rand(5, 10), Rand(10, 20), releaseTime: Rand(10, 20)), gate);
	Out.ar(outBus,  Pan2.ar(sig * env * amp, Rand(-1, 1), 0.5))
})
)


//notes initialization, with gate set to 0 -> notes played in silence
(
~crackle = ~synth.note.theta_(0).bpfFreq_(1000).rq_(100).buffer_(a).gate_(0).theta_(CtkControl.lfo(LFNoise2, 2, -pi/4, pi/4)).amp_(1.0).play;
~water = ~synth.note.buffer_(c).gate_(0).rq_(10).amp_(0.8).rotAngle_(CtkControl.lfo(LFNoise2, 0.1, -pi, pi)).play;  //ldr0Val ->rate
~click = ~synth.note.buffer_(b).gate_(0).amp_(1.0).rq_(10).theta_(pi/4).play; //ldr1Val -> gate
~chant = ~synth.note.gate_(0).amp_(0.5).buffer_(e).rq_(20).play;  //ldr2Val ->amp
~bubble = ~synth.note.buffer_(f).rq_(20).amp_(3.0).gate_(0).theta_(-pi/4).play;  //ldr3Val -> gate
~distance = ~synth.note.buffer_(d).gate_(0).rate_(1).amp_(1.0).rq_(1.0).bpfFreq_(100).rotAngle_(CtkControl.lfo(LFNoise2, 0.2, -pi, pi)).play; //ldr4Val-> bpfFreq
);

//threshhold for each ldr sensor value to triggue the gate/signal processing
(
~thresh0 = 75; ~thresh1 = 200; ~thresh2 = 75;~thresh3 = 75; ~thresh4 = 75;
)

// to trigger the notes so they can be heard
(
~notes = Routine({
	{
		if(~ldr0Val>~thresh0,
			{~water.gate_(1); ~water.rate_(~ldr0Val.linexp(~thresh0, 200, 1.0, 4.0))}, {~water.gate_(0)});  //ldr0Val
		if(~ldr1Val>~thresh1,
			{~click.gate_(1); ~click.theta_(~ldr1Val.linlin(~thresh1, 350, -2pi, 2pi))}, {~click.gate_(0)}); //ldr1Val
		if(~ldr2Val>~thresh2,
			{~chant.gate_(1); ~chant.amp_(~ldr2Val.linexp(~thresh2, 250, 0.5, 2.5))}, {~chant.gate_(0)}); //ldr2Val
		if(~ldr3Val > ~thresh3, 
			{~bubble.gate_(1)}, {~bubble.gate_(0)});  //ldr3Val
		if(~ldr4Val > ~thresh4, 
			{~distance.gate_(1); ~distance.bpfFreq_(~ldr4Val.linexp(~thresh4, 450, 100, 1000.0))}, {~distance.gate_(0)});//ldr4Val
		0.01.wait;
	}.loop
}).play
)
~notes.stop. // to stop all notes being played
Buffer.freeAll // clear buffers
