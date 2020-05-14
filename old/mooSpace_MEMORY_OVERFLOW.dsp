declare name "mooSpace";
declare description "variable space reverberation audio effect";
declare author "Arev Imer (arev.imer@students.fhnw.ch)";
declare copyright "Arev";
declare version "0.1";

import("stdfaust.lib");

// stuff:
// "cascading": allpass, _ : _, +(_,_)
//	_ <:(//wet split
//		(feeder1,//left branch
//		feeder2)//right branch
//		~(*(10), *(10)))

// Controls

// input_level = vbargraph("h:mooSpace/h:Levels/[0]in", -60, 0) ;
// output_level = vbargraph("h:mooSpace/h:Levels/[1]out", -60, 0);
// clipping_led = vbargraph("h:mooSpace/h:Levels/[2]clip[style:led]", -6, 0);


diff_mult = hslider("smear", 1, 0.001, 25, 0.001) : si.smooth(0.999);
late_diff = hslider("drag", 1, 0.001, 10, 0.001) : si.smooth(0.999);
decay  = hslider("decay", 0.5, 0.001, 0.999, 0.001);

predelay = hslider("lag", 0.1, 0.1, 256, 1) : si.smoo;
reson = hslider("bump", 1, 0.5, 1.33, 0.0001) : si.smoo;
damp = hslider("colour", 0.2, 0.001, 1, 0.001);
mod = hslider("modulate", 0.2, 0, 1, 0.01) : _ * ((no.lfnoiseN(3, 10) + 1)/2) :_* 50 : ba.ramp(1000);
rev_mix = hslider("mix", 0.5, 0, 1, 0.01) : si.smoo;
dist_amt = hslider("push", 0, 0, 1, 0.01) : si.smoo;
dtime = hslider("reverse", 200, 0, 1000, 0.1) : si.smoo : _ * 88.2 ;
ducktime = 0.2 * (dtime/2);

highcut = hslider("High Cut", 15000, 20, 15000, 0.01) : si.smoo;
lowcut = hslider("Low Cut", 20, 20, 5000, 0.01) : si.smoo;
 

reverse = checkbox("reverse");


// Parameters

bwidth = 0.9995;


i_diff_1 = 0.75;
i_diff_2 = 0.625;

d_diff_1 = 0.7;
d_diff_2 = 0.6;


dt_idl_1	= 142;
dt_idl_2	= 107;
dt_idl_3	= 379;
dt_idl_4	= 277;

dt_idr_1	= 151;
dt_idr_2	= 101;
dt_idr_3	= 367;
dt_idr_4	= 281;

dt_fbd_1	= 149;
dt_fbd_2	= 113;
dt_fbd_3	= 397;
dt_fbd_4	= 283;


dt_late_l1 = 672;
dt_late_l2 = 1800;
dt_late_r1 = 908;
dt_late_r2 = 2656;


rev_dt_1 = 4453;
rev_dt_2 = 3720;
rev_dt_3 = 4217;
rev_dt_4 = 3163;


// Functions

swap = _,_ <: !,_,_,!;	


mixer(mix, dry_l, wet_l, dry_r, wet_r) = sel(mix, dry_l, wet_l), sel(mix, dry_r, wet_r)
	with { 
			sel(mix, dry, wet) = (1-mix) * dry + mix * wet;
		  };


allpass(dmax, dt, coeff) = 
(+ <: de.fdelay2(dmax, dt-1),*(coeff)) ~ *(-coeff) : mem,_ : + ;


bandwidth(x) = _ * x : + ~ (mem * (1 - x));


damping(x) = _ * (1 - x) : + ~ (mem * x);


input_proc(dt, bw) =

	(_ + _) * 0.5 : ef.cubicnl(dist_amt,0) : de.fdelay(8820, dt*44.1)  : bandwidth(bw) : _;


input_diff_l =
	fi.allpass_fcomb(26*dt_idl_1, diff_mult*dt_idl_1+mod, i_diff_1) :
	fi.allpass_fcomb(26*dt_idl_2, diff_mult*dt_idl_2-mod, i_diff_1) :
	fi.allpass_fcomb(26*dt_idl_3, diff_mult*dt_idl_3+mod, i_diff_2) :
	fi.allpass_fcomb(26*dt_idl_4, diff_mult*dt_idl_4-mod, i_diff_2) :
	_;

input_diff_r =
	fi.allpass_fcomb(26*dt_idr_1, diff_mult*dt_idr_1+mod, i_diff_1) :
	fi.allpass_fcomb(26*dt_idr_2, diff_mult*dt_idr_2-mod, i_diff_1) :
	fi.allpass_fcomb(26*dt_idr_3, diff_mult*dt_idr_3+mod, i_diff_2) :
	fi.allpass_fcomb(26*dt_idr_4, diff_mult*dt_idr_4-mod, i_diff_2) :
	_;

feedback_diff =
	allpass(26*dt_fbd_1, diff_mult*dt_fbd_1+mod, i_diff_1) :
	allpass(26*dt_fbd_2, diff_mult*dt_fbd_2-mod, i_diff_1) : 
	allpass(26*dt_fbd_3, diff_mult*dt_fbd_3+mod, i_diff_2) :
	allpass(26*dt_fbd_4, diff_mult*dt_fbd_4-mod, i_diff_2) :
	_;


//////// OLD BRANCH PROCESSING ////////
// left_side =
// 	_*0.5+_*0.3 : allpass(10*dt_late_l1, dt_late_l1, -d_diff_1)
// 	<: de.fdelay2(5 * rev_dt_1, rev_dt_1), _ : damping(damp), _ : decay * _, _ :
// 	allpass(10*dt_late_l2, dt_late_l2, d_diff_2) , _ :
// 	de.fdelay2(5 * rev_dt_2, rev_dt_2), _ : _ * decay , _;

// right_side =
// 	_*0.5+_*0.3 : allpass(10*dt_late_r1, dt_late_r1, -d_diff_1)
// 	<: de.fdelay2(5 * rev_dt_3, rev_dt_3), _ : damping(damp), _ : decay * _, _ :
// 	allpass(10*dt_late_r2, dt_late_r2, d_diff_2) , _ :
// 	de.fdelay2(5 * rev_dt_4, rev_dt_4), _ : _ * decay , _;

multi_tap_allpass_l(dt, coeff) =

	(+ <: de.fdelay2(10*dt+50, late_diff*dt-1+mod), * (coeff), de.fdelay2(1.04*dt, late_diff*dt/9.63),de.fdelay2(6.85*dt, late_diff*dt/1.46))
	~(* (-coeff), !, !, !) : mem, _, _, _ : +(_, _), _, _;


multi_tap_allpass_r(dt, coeff) =

	(+ <: de.fdelay2(10*dt+50, late_diff*dt-1+mod), * (coeff), de.fdelay2(1.27*dt, late_diff*dt/7.93),de.fdelay2(7.2*dt, late_diff*dt/1.39))
	~(* (-coeff), !, !, !) : mem, _, _, _ : +(_, _), _, _;


left_side = 
	
	_ * (decay), _ : + : fi.allpass_fcomb(10*dt_late_l1, dt_late_l1, -d_diff_1)

	<: de.fdelay2(5 * rev_dt_1, rev_dt_1),
	de.fdelay2(2.24 * rev_dt_1, rev_dt_1/2.23), // node24_30[1990] -> L-
	de.fdelay2(0.4 * rev_dt_1, rev_dt_1/12.61), // node24_30[353] -> R+
	de.fdelay2(4.1 * rev_dt_1, rev_dt_1/1.23) : // node24_30[3627] -> R+

	damping(damp), _, _+_ :
	
	decay * _, _, _ :


	(multi_tap_allpass_l(dt_late_l2, d_diff_2), _, _) <: // node31_33[187] -> L-, node31_33[1228] -> R-
	de.fdelay2(5 * rev_dt_2+50, rev_dt_2+mod), _, _, _, _,
	de.fdelay2(3.6 * rev_dt_2, rev_dt_2/1.39), !, !, !, !, // node33_39[2673] -> R+
	de.fdelay2(1.44 * rev_dt_2, rev_dt_2/3.49), !, !, !, ! : // node33_39[1066] -> L-
	
	_ * decay , _/*Lmult-*/,/*Rmult-*/ swap/*Lprev-*/, _/*Rsum+*/, _/*R+*/, _/*L-*/ :
	_, _, _, 0.6*((-1* _) + _ + _), _ :
	_, _, _, swap :
	_, 0.6*((-1* _) - _ - _), _; // 2nd GOING TO LEFT OUT / 3rd GOING TO RIGHT OUT


right_side = 

	_ * (decay), _ : + : fi.allpass_fcomb(10*dt_late_r1, dt_late_r1, -d_diff_1)

	<: de.fdelay2(5 * rev_dt_3, rev_dt_3),
	de.fdelay2(2.5 * rev_dt_3, rev_dt_3/2.0), // node48_54[2111] -> R-
	de.fdelay2(0.32 * rev_dt_3, rev_dt_3/15.85), // node48_54[266] -> L+
	de.fdelay2(3.53 * rev_dt_3, rev_dt_3/1.42) : // node48_54[2974]-> L+

	damping(damp), _, _ + _ :
	
	decay * _, _, _ :

	(multi_tap_allpass_r(dt_late_r2, d_diff_2), _, _) <: // node55_59[335] -> R-, node55_59[1913] -> L-
	de.fdelay2(5 * rev_dt_4+50, rev_dt_4+mod), _, _, _, _,
	de.fdelay2(0.2 * rev_dt_4, rev_dt_4/26.14), !, !, !, !, // node59_63[121] -> L-
	de.fdelay2(3.17 * rev_dt_4, rev_dt_4/1.58), !, !, !, !: // node59_63[1996] -> R+
	
	_ * decay , _/*Rmult-*/,/*Lmult-*/swap/*Rprev-*/, _/*Lsum*/, _/*L-*/, _/*R+*/ :
	_, _, _, 0.6*((-1* _) + _ - _), _ :
	_, _, _, swap :
	_, 0.6*((-1* _) - _ + _), _ : // 2nd GOING TO RIGHT OUT / 3rd GOING TO LEFT OUT
	_, swap; // 2nd GOING TO LEFT OUT / 3rd GOING TO RIGHT OUT



reversedelay(delMax,phase,speed) = grooveduck * de.fdelay2(88200, del) with {
  sin_window = (del/delMax) * ma.PI : sin;
  grooveduck = del > (dtime - ducktime) : 1 - _ : ba.ramp(ducktime) ;
  delOffset = delMax * max(0,min(0.999999,phase)); // starting point in delay line
  del = ((speed * os.lf_rawsaw(delMax/speed)) + delOffset) % (delMax-1);
};


process = _ ,_ 
    //<: _, swap, _ : _, _, +/2 : _, attach(_, an.amp_follower(0.1) : ba.linear2db : input_level)
    
    <: // split L/R to dry and wet

	(_, // left ch dry

	(/*input_proc(predelay, bwidth)*/ /*ba.bypass2(1-reverse,par(i,2, reversedelay(dtime, 0, 2))) : */par(i,2,ef.cubicnl(dist_amt,0) : de.fdelay(11290, predelay*44.1) : fi.lowpass(3,highcut) : fi.highpass(3,lowcut)) : input_diff_l, input_diff_r   /*<: _, _*/) // sum l/r in input_proc, split summed & processed  left/right to 2 ch

	, _) : // right ch dry

	(_, // left ch dry

		(_, // 1st in left_side

			swap, // swap 3 & 2 that feedback goes to 1st in on right_side

			_ : // 2nd in right_side

		(left_side, right_side): 

		_, _, swap, _, _ : _, swap, _, _, _) ~ (swap : par(i, 2, feedback_diff): co.compressor_stereo(5, -6, 1, 3))),

	_ : // right ch dry

	_, !, !, _, swap, _, _ :

	_, (_ ,_ :> _), (_, _ :> _), _ : _, _, swap  :mixer(rev_mix): co.limiter_1176_R4_stereo; /*<: _, swap, _ : _, _, +/2 : _, attach(_, (abs : an.amp_follower(0.1) : ba.linear2db : clipping_led : output_level));*/