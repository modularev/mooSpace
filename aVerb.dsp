import("stdfaust.lib");

// stuff:
// "cascading": allpass, _ : _, +(_,_)
//	_ <:(//wet split
//		(feeder1,//left branch
//		feeder2)//right branch
//		~(*(10), *(10)))

// Controls

predelay = hslider("Pre-delay", 10, 0.1, 300, 1);

diff_mult = hslider("Input Diffusion", 1, 0.1, 25, 0.001) : si.smoo;

decay  = hslider("Room Size", 0.5, 0.001, 0.999, 0.001) : si.smoo;

damp = hslider("Brightness", 0.2, 0, 1, 0.01);

rev_mix = hslider("Wet/Dry", 0.5, 0, 1, 0.01) : si.smoo;


// Parameters

bwidth = 0.9995;


i_diff_1 = 0.75;
i_diff_2 = 0.625;

d_diff_1 = 0.7;
d_diff_2 = 0.5;


dt_id_1	= 142;
dt_id_2	= 107;
dt_id_3	= 379;
dt_id_4	= 277;


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


allpass(dmax, dt, diff) = 
(+ <: de.fdelay2a(dmax, dt-1),*(diff)) ~ *(-diff) : mem,_ : + ;


bandwidth(x) = _ * x : + ~ (mem * (1 - x));


damping(x) = _ * (1 - x) : + ~ (mem * x);


input_proc(dt, bw) =

	(_ + _) *0.5 : @(dt) : bandwidth(bw) : _;


input_diff =
	allpass(30*dt_id_1, diff_mult*dt_id_1, i_diff_1) :
	allpass(30*dt_id_2, diff_mult*dt_id_2, i_diff_1) :
	allpass(30*dt_id_3, diff_mult*dt_id_3, i_diff_2) :
	allpass(30*dt_id_4, diff_mult*dt_id_4, i_diff_2) :
	_;

//////// OLD BRANCH PROCESSING ////////
// left_side =
// 	_*0.5+_*0.3 : allpass(10*dt_late_l1, dt_late_l1, -d_diff_1)
// 	<: de.fdelay2a(5 * rev_dt_1, rev_dt_1), _ : damping(damp), _ : decay * _, _ :
// 	allpass(10*dt_late_l2, dt_late_l2, d_diff_2) , _ :
// 	de.fdelay2a(5 * rev_dt_2, rev_dt_2), _ : _ * decay , _;

// right_side =
// 	_*0.5+_*0.3 : allpass(10*dt_late_r1, dt_late_r1, -d_diff_1)
// 	<: de.fdelay2a(5 * rev_dt_3, rev_dt_3), _ : damping(damp), _ : decay * _, _ :
// 	allpass(10*dt_late_r2, dt_late_r2, d_diff_2) , _ :
// 	de.fdelay2a(5 * rev_dt_4, rev_dt_4), _ : _ * decay , _;

multi_tap_allpass_l(dt, diff) =

	(+ <: de.fdelay2a(10*dt, dt-1), * (diff), de.fdelay2a(1.04*dt, dt/9.63),de.fdelay2a(6.85*dt, dt/1.46))
	~(* (-diff), !, !, !) : mem, _, _, _ : +(_, _), _, _;


multi_tap_allpass_r(dt, diff) =

	(+ <: de.fdelay2a(10*dt, dt-1), * (diff), de.fdelay2a(1.27*dt, dt/7.93),de.fdelay2a(7.2*dt, dt/1.39))
	~(* (-diff), !, !, !) : mem, _, _, _ : +(_, _), _, _;


left_side = 
	
	+ : allpass(10*dt_late_l1, dt_late_l1, -d_diff_1)

	<: de.fdelay2a(5 * rev_dt_1, rev_dt_1),
	de.fdelay2a(2.24 * rev_dt_1, rev_dt_1/2.23), // node24_30[1990] -> L-
	de.fdelay2a(0.4 * rev_dt_1, rev_dt_1/12.61), // node24_30[353] -> R+
	de.fdelay2a(4.1 * rev_dt_1, rev_dt_1/1.23) : // node24_30[3627] -> R+

	damping(damp), _, _+_ :
	
	decay * _, _, _ :


	(multi_tap_allpass_l(dt_late_l2, d_diff_2), _, _) <: // node31_33[187] -> L-, node31_33[1228] -> R-
	de.fdelay2a(5 * rev_dt_2, rev_dt_2), _, _, _, _,
	de.fdelay2a(3.6 * rev_dt_2, rev_dt_2/1.39), !, !, !, !, // node33_39[2673] -> R+
	de.fdelay2a(1.44 * rev_dt_2, rev_dt_2/3.49), !, !, !, ! : // node33_39[1066] -> L-
	
	_ * decay , _/*Lmult-*/,/*Rmult-*/ swap/*Lprev-*/, _/*Rsum+*/, _/*R+*/, _/*L-*/ :
	_, _, _, 0.6*((-1* _) + _ + _), _ :
	_, _, _, swap :
	_, 0.6*((-1* _) - _ - _), _; // 2nd GOING TO LEFT OUT / 3rd GOING TO RIGHT OUT


right_side = 

	+ : allpass(10*dt_late_r1, dt_late_r1, -d_diff_1)

	<: de.fdelay2a(5 * rev_dt_3, rev_dt_3),
	de.fdelay2a(2.5 * rev_dt_3, rev_dt_3/2.0), // node48_54[2111] -> R-
	de.fdelay2a(0.32 * rev_dt_3, rev_dt_3/15.85), // node48_54[266] -> L+
	de.fdelay2a(3.53 * rev_dt_3, rev_dt_3/1.42) : // node48_54[2974]-> L+

	damping(damp), _, _ + _ :
	
	decay * _, _, _ :

	(multi_tap_allpass_r(dt_late_r2, d_diff_2), _, _) <: // node55_59[335] -> R-, node55_59[1913] -> L-
	de.fdelay2a(5 * rev_dt_4, rev_dt_4), _, _, _, _,
	de.fdelay2a(0.2 * rev_dt_4, rev_dt_4/26.14), !, !, !, !, // node59_63[121] -> L-
	de.fdelay2a(3.17 * rev_dt_4, rev_dt_4/1.58), !, !, !, !: // node59_63[1996] -> R+
	
	_ * decay , _/*Rmult-*/,/*Lmult-*/swap/*Rprev-*/, _/*Lsum*/, _/*L-*/, _/*R+*/ :
	_, _, _, 0.6*((-1* _) + _ - _), _ :
	_, _, _, swap :
	_, 0.6*((-1* _) - _ + _), _ : // 2nd GOING TO RIGHT OUT / 3rd GOING TO LEFT OUT
	_, swap; // 2nd GOING TO LEFT OUT / 3rd GOING TO RIGHT OUT



process = _ ,_ <: // split L/R to dry and wet

	(_, // left ch dry

	(input_proc(predelay*44.1, bwidth) : input_diff <: _, _) // sum l/r in input_proc, split summed & processed  left/right to 2 ch

	, _) : // right ch dry

	(_, // left ch dry

		(_, // 1st in left_side

			swap, // swap 3 & 2 that feedback goes to 1st in on right_side

			_ : // 2nd in right_side

		(left_side, right_side): 

		_, _, swap, _, _ : _, swap, _, _, _) ~ (swap : _*(decay), _*(decay))),

	_ : // right ch dry

	_, !, !, _, swap, _, _ :

	_, (_ ,_ :> _), (_, _ :> _), _ : _, _, swap : mixer(rev_mix);