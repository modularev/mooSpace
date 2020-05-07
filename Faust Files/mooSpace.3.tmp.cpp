/* ------------------------------------------------------------
author: "Arev Imer (arev.imer@students.fhnw.ch)"
copyright: "Arev"
name: "mooSpace"
version: "0.1"
Code generated with Faust 2.23.8 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider3;
	float fRec26[2];
	FAUSTFLOAT fHslider4;
	float fRec27[2];
	int IOTA;
	float fVec1[16384];
	FAUSTFLOAT fHslider5;
	float fRec28[2];
	float fVec2[2];
	float fRec25[2];
	float fRec24[3];
	float fVec3[2];
	FAUSTFLOAT fHslider6;
	float fRec29[2];
	float fRec23[2];
	float fRec22[3];
	float fVec4[4096];
	FAUSTFLOAT fHslider7;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec34[2];
	float fRec35[2];
	int iRec36[2];
	float fRec33[2];
	float fRec32[2];
	float fConst10;
	float fConst11;
	float fRec31[3];
	float fRec30[2];
	FAUSTFLOAT fHslider8;
	float fRec37[2];
	float fRec20[2];
	float fVec5[4096];
	float fRec18[2];
	float fVec6[16384];
	float fRec16[2];
	float fVec7[8192];
	float fRec14[2];
	float fVec8[4096];
	float fRec44[2];
	float fVec9[4096];
	float fRec42[2];
	float fVec10[16384];
	float fRec40[2];
	float fVec11[8192];
	float fRec38[2];
	float fConst12;
	float fConst13;
	float fVec12[4096];
	float fRec55[2];
	float fVec13[4096];
	float fRec53[2];
	float fVec14[16384];
	float fRec51[2];
	float fVec15[8192];
	float fRec49[2];
	float fConst14;
	float fConst15;
	float fRec48[2];
	float fRec47[2];
	float fRec46[2];
	float fVec16[1024];
	float fRec12[2];
	float fVec17[8192];
	float fRec11[3];
	float fVec18[32768];
	FAUSTFLOAT fHslider9;
	float fRec57[2];
	float fRec7[2];
	float fVec19[32768];
	float fRec1[2];
	float fVec20[16384];
	float fVec21[2];
	float fRec76[2];
	float fRec75[3];
	float fVec22[2];
	float fRec74[2];
	float fRec73[3];
	float fVec23[4096];
	float fRec71[2];
	float fVec24[4096];
	float fRec69[2];
	float fVec25[16384];
	float fRec67[2];
	float fVec26[8192];
	float fRec65[2];
	float fVec27[1024];
	float fRec63[2];
	float fVec28[8192];
	float fRec62[3];
	float fVec29[32768];
	float fRec58[2];
	float fVec30[16384];
	float fRec2[2];
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec79[2];
	float fRec78[2];
	float fRec77[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("author", "Arev Imer (arev.imer@students.fhnw.ch)");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.0");
		m->declare("copyright", "Arev");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("description", "variable space reverberation audio effect");
		m->declare("filename", "mooSpace.3.tmp.dsp");
		m->declare("filters.lib/allpass_fcomb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_fcomb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_fcomb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "mooSpace");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "0.1");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = std::tan((31.415926f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 1.0f) / fConst2) + 1.0f));
		fConst5 = (1.0f / (fConst3 + 1.0f));
		fConst6 = (1.0f - fConst3);
		fConst7 = (62.831852f / fConst0);
		fConst8 = std::sin(fConst7);
		fConst9 = std::cos(fConst7);
		fConst10 = (((fConst3 + -1.0f) / fConst2) + 1.0f);
		fConst11 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst2))));
		fConst12 = std::exp((0.0f - (2.0f / fConst0)));
		fConst13 = (1.0f - fConst12);
		fConst14 = std::exp((0.0f - (1.0f / fConst0)));
		fConst15 = std::exp((0.0f - (0.333333343f / fConst0)));
		fConst16 = std::exp((0.0f - (2500.0f / fConst0)));
		fConst17 = (1.0f - fConst16);
		fConst18 = std::exp((0.0f - (1250.0f / fConst0)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.20000000000000001f);
		fHslider3 = FAUSTFLOAT(15000.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.10000000000000001f);
		fHslider6 = FAUSTFLOAT(20.0f);
		fHslider7 = FAUSTFLOAT(0.20000000000000001f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec26[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec27[l3] = 0.0f;
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 16384); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec28[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec25[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec24[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec3[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec29[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec23[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec22[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec34[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec35[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			iRec36[l16] = 0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec33[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec32[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec31[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec30[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec37[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 4096); l23 = (l23 + 1)) {
			fVec5[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 16384); l25 = (l25 + 1)) {
			fVec6[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec16[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 8192); l27 = (l27 + 1)) {
			fVec7[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec14[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 4096); l29 = (l29 + 1)) {
			fVec8[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec44[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec9[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec42[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 16384); l33 = (l33 + 1)) {
			fVec10[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec40[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 8192); l35 = (l35 + 1)) {
			fVec11[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec38[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			fVec12[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec55[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			fVec13[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec53[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			fVec14[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec51[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 8192); l43 = (l43 + 1)) {
			fVec15[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec49[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec48[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec47[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec46[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 1024); l48 = (l48 + 1)) {
			fVec16[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec12[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 8192); l50 = (l50 + 1)) {
			fVec17[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec11[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 32768); l52 = (l52 + 1)) {
			fVec18[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec57[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec7[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 32768); l55 = (l55 + 1)) {
			fVec19[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec1[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 16384); l57 = (l57 + 1)) {
			fVec20[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fVec21[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec76[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec75[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec22[l61] = 0.0f;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec74[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec73[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 4096); l64 = (l64 + 1)) {
			fVec23[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec71[l65] = 0.0f;
		}
		for (int l66 = 0; (l66 < 4096); l66 = (l66 + 1)) {
			fVec24[l66] = 0.0f;
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec69[l67] = 0.0f;
		}
		for (int l68 = 0; (l68 < 16384); l68 = (l68 + 1)) {
			fVec25[l68] = 0.0f;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec67[l69] = 0.0f;
		}
		for (int l70 = 0; (l70 < 8192); l70 = (l70 + 1)) {
			fVec26[l70] = 0.0f;
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec65[l71] = 0.0f;
		}
		for (int l72 = 0; (l72 < 1024); l72 = (l72 + 1)) {
			fVec27[l72] = 0.0f;
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec63[l73] = 0.0f;
		}
		for (int l74 = 0; (l74 < 8192); l74 = (l74 + 1)) {
			fVec28[l74] = 0.0f;
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec62[l75] = 0.0f;
		}
		for (int l76 = 0; (l76 < 32768); l76 = (l76 + 1)) {
			fVec29[l76] = 0.0f;
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec58[l77] = 0.0f;
		}
		for (int l78 = 0; (l78 < 16384); l78 = (l78 + 1)) {
			fVec30[l78] = 0.0f;
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec2[l79] = 0.0f;
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec79[l80] = 0.0f;
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec78[l81] = 0.0f;
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec77[l82] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("mooSpace");
		ui_interface->addHorizontalSlider("High Cut", &fHslider3, 15000.0f, 20.0f, 15000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Low Cut", &fHslider6, 20.0f, 20.0f, 5000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("colour", &fHslider2, 0.200000003f, 0.00100000005f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("decay", &fHslider1, 0.5f, 0.00100000005f, 0.999000013f, 0.00100000005f);
		ui_interface->addHorizontalSlider("drag", &fHslider9, 1.0f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("lag", &fHslider5, 0.100000001f, 0.100000001f, 256.0f, 1.0f);
		ui_interface->addHorizontalSlider("mix", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("modulate", &fHslider7, 0.200000003f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("push", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("smear", &fHslider8, 1.0f, 0.00100000005f, 25.0f, 0.00100000005f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		float fSlow2 = float(fHslider2);
		float fSlow3 = (1.0f - fSlow2);
		float fSlow4 = (0.00100000005f * float(fHslider3));
		float fSlow5 = (0.00100000005f * float(fHslider4));
		float fSlow6 = (0.00100000005f * float(fHslider5));
		float fSlow7 = (0.00100000005f * float(fHslider6));
		float fSlow8 = (25.0f * float(fHslider7));
		float fSlow9 = (0.00100000005f * float(fHslider8));
		float fSlow10 = (0.00100000005f * float(fHslider9));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec26[0] = (fSlow4 + (0.999000013f * fRec26[1]));
			float fTemp0 = std::tan((fConst1 * fRec26[0]));
			float fTemp1 = (1.0f / fTemp0);
			float fTemp2 = (1.0f - fTemp1);
			float fTemp3 = float(input1[i]);
			fRec27[0] = (fSlow5 + (0.999000013f * fRec27[1]));
			float fTemp4 = std::pow(10.0f, (2.0f * fRec27[0]));
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fTemp3 * fTemp4)));
			float fTemp6 = (fTemp5 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp5))));
			fVec1[(IOTA & 16383)] = fTemp6;
			fRec28[0] = (fSlow6 + (0.999000013f * fRec28[1]));
			float fTemp7 = (44.0999985f * fRec28[0]);
			int iTemp8 = int(fTemp7);
			int iTemp9 = std::min<int>(11291, std::max<int>(0, iTemp8));
			float fTemp10 = std::floor(fTemp7);
			float fTemp11 = (fTemp10 + (1.0f - fTemp7));
			float fTemp12 = (fTemp7 - fTemp10);
			int iTemp13 = std::min<int>(11291, std::max<int>(0, (iTemp8 + 1)));
			float fTemp14 = ((fVec1[((IOTA - iTemp9) & 16383)] * fTemp11) + (fTemp12 * fVec1[((IOTA - iTemp13) & 16383)]));
			fVec2[0] = fTemp14;
			float fTemp15 = (fTemp1 + 1.0f);
			fRec25[0] = (0.0f - (((fRec25[1] * fTemp2) - (fTemp14 + fVec2[1])) / fTemp15));
			float fTemp16 = (((fTemp1 + -1.0f) / fTemp0) + 1.0f);
			float fTemp17 = (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)));
			float fTemp18 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			fRec24[0] = (fRec25[0] - (((fRec24[2] * fTemp16) + (2.0f * (fRec24[1] * fTemp17))) / fTemp18));
			float fTemp19 = (fRec24[2] + (fRec24[0] + (2.0f * fRec24[1])));
			fVec3[0] = (fTemp19 / fTemp18);
			fRec29[0] = (fSlow7 + (0.999000013f * fRec29[1]));
			float fTemp20 = std::tan((fConst1 * fRec29[0]));
			float fTemp21 = (1.0f / fTemp20);
			float fTemp22 = (fTemp21 + 1.0f);
			float fTemp23 = (0.0f - (1.0f / (fTemp20 * fTemp22)));
			float fTemp24 = (1.0f - fTemp21);
			float fTemp25 = (fTemp20 * fTemp18);
			fRec23[0] = ((fVec3[1] * fTemp23) - (((fRec23[1] * fTemp24) - (fTemp19 / fTemp25)) / fTemp22));
			float fTemp26 = (((fTemp21 + -1.0f) / fTemp20) + 1.0f);
			float fTemp27 = mydsp_faustpower2_f(fTemp20);
			float fTemp28 = (1.0f - (1.0f / fTemp27));
			float fTemp29 = (((fTemp21 + 1.0f) / fTemp20) + 1.0f);
			fRec22[0] = (fRec23[0] - (((fRec22[2] * fTemp26) + (2.0f * (fRec22[1] * fTemp28))) / fTemp29));
			float fTemp30 = (0.0f - (2.0f / fTemp27));
			float fTemp31 = (((((fRec22[1] * fTemp30) + (fRec22[0] / fTemp27)) + (fRec22[2] / fTemp27)) / fTemp29) - (0.75f * fRec20[1]));
			fVec4[(IOTA & 4095)] = fTemp31;
			float fTemp32 = (fRec30[1] + 0.00100000005f);
			fRec34[0] = ((fConst8 * fRec35[1]) + (fConst9 * fRec34[1]));
			fRec35[0] = ((float((1 - iVec0[1])) + (fConst9 * fRec35[1])) - (fConst8 * fRec34[1]));
			int iTemp33 = ((fRec34[1] <= 0.0f) & (fRec34[0] > 0.0f));
			iRec36[0] = ((1103515245 * iRec36[1]) + 12345);
			fRec33[0] = ((fRec33[1] * float((1 - iTemp33))) + (4.65661287e-10f * (float(iRec36[0]) * float(iTemp33))));
			fRec32[0] = (0.0f - (fConst5 * ((fConst6 * fRec32[1]) - (fRec33[0] + fRec33[1]))));
			fRec31[0] = (fRec32[0] - (fConst4 * ((fConst10 * fRec31[2]) + (fConst11 * fRec31[1]))));
			float fTemp34 = (fSlow8 * ((fConst4 * (fRec31[2] + (fRec31[0] + (2.0f * fRec31[1])))) + 1.0f));
			float fTemp35 = (fRec30[1] + -0.00100000005f);
			fRec30[0] = ((fTemp32 < fTemp34) ? fTemp32 : ((fTemp35 > fTemp34) ? fTemp35 : fTemp34));
			fRec37[0] = (fSlow9 + (0.999000013f * fRec37[1]));
			float fTemp36 = (fRec30[0] + (142.0f * fRec37[0]));
			float fTemp37 = (fTemp36 + -1.0f);
			int iTemp38 = int(fTemp37);
			float fTemp39 = std::floor(fTemp37);
			fRec20[0] = ((fVec4[((IOTA - std::min<int>(3693, int(std::max<int>(0, int(iTemp38))))) & 4095)] * (fTemp39 + (2.0f - fTemp36))) + ((fTemp36 + (-1.0f - fTemp39)) * fVec4[((IOTA - std::min<int>(3693, int(std::max<int>(0, int((iTemp38 + 1)))))) & 4095)]));
			float fRec21 = (0.75f * fTemp31);
			float fTemp40 = ((fRec21 + fRec20[1]) - (0.75f * fRec18[1]));
			fVec5[(IOTA & 4095)] = fTemp40;
			float fTemp41 = (107.0f * fRec37[0]);
			float fTemp42 = (-1.0f - fRec30[0]);
			float fTemp43 = (fTemp41 + fTemp42);
			int iTemp44 = int(fTemp43);
			float fTemp45 = (fRec30[0] + std::floor(fTemp43));
			fRec18[0] = ((fVec5[((IOTA - std::min<int>(2783, int(std::max<int>(0, int(iTemp44))))) & 4095)] * (fTemp45 + (2.0f - fTemp41))) + ((fTemp41 + (-1.0f - fTemp45)) * fVec5[((IOTA - std::min<int>(2783, int(std::max<int>(0, int((iTemp44 + 1)))))) & 4095)]));
			float fRec19 = (0.75f * fTemp40);
			float fTemp46 = ((fRec19 + fRec18[1]) - (0.625f * fRec16[1]));
			fVec6[(IOTA & 16383)] = fTemp46;
			float fTemp47 = (fRec30[0] + (379.0f * fRec37[0]));
			float fTemp48 = (fTemp47 + -1.0f);
			int iTemp49 = int(fTemp48);
			float fTemp50 = std::floor(fTemp48);
			fRec16[0] = ((fVec6[((IOTA - std::min<int>(9855, int(std::max<int>(0, int(iTemp49))))) & 16383)] * (fTemp50 + (2.0f - fTemp47))) + ((fTemp47 + (-1.0f - fTemp50)) * fVec6[((IOTA - std::min<int>(9855, int(std::max<int>(0, int((iTemp49 + 1)))))) & 16383)]));
			float fRec17 = (0.625f * fTemp46);
			float fTemp51 = ((fRec17 + fRec16[1]) - (0.625f * fRec14[1]));
			fVec7[(IOTA & 8191)] = fTemp51;
			float fTemp52 = (277.0f * fRec37[0]);
			float fTemp53 = (fTemp52 + fTemp42);
			int iTemp54 = int(fTemp53);
			float fTemp55 = (fRec30[0] + std::floor(fTemp53));
			fRec14[0] = ((fVec7[((IOTA - std::min<int>(7203, int(std::max<int>(0, int(iTemp54))))) & 8191)] * (fTemp55 + (2.0f - fTemp52))) + ((fTemp52 + (-1.0f - fTemp55)) * fVec7[((IOTA - std::min<int>(7203, int(std::max<int>(0, int((iTemp54 + 1)))))) & 8191)]));
			float fRec15 = (0.625f * fTemp51);
			float fTemp56 = (fRec2[1] - (0.75f * fRec44[1]));
			fVec8[(IOTA & 4095)] = fTemp56;
			float fTemp57 = (fRec30[0] + (149.0f * fRec37[0]));
			float fTemp58 = (fTemp57 + -1.49999499f);
			int iTemp59 = int(fTemp58);
			int iTemp60 = std::min<int>(3874, int(std::max<int>(0, int(iTemp59))));
			float fTemp61 = std::floor(fTemp58);
			float fTemp62 = (fTemp57 + (-2.0f - fTemp61));
			float fTemp63 = (0.0f - fTemp62);
			float fTemp64 = (fTemp57 + (-3.0f - fTemp61));
			float fTemp65 = (0.0f - (0.5f * fTemp64));
			float fTemp66 = (fTemp57 + (-1.0f - fTemp61));
			int iTemp67 = std::min<int>(3874, int(std::max<int>(0, int((iTemp59 + 1)))));
			float fTemp68 = (0.0f - fTemp64);
			int iTemp69 = std::min<int>(3874, int(std::max<int>(0, int((iTemp59 + 2)))));
			fRec44[0] = (((fVec8[((IOTA - iTemp60) & 4095)] * fTemp63) * fTemp65) + (fTemp66 * ((fVec8[((IOTA - iTemp67) & 4095)] * fTemp68) + (0.5f * (fTemp62 * fVec8[((IOTA - iTemp69) & 4095)])))));
			float fRec45 = (0.75f * fTemp56);
			float fTemp70 = ((fRec45 + fRec44[1]) - (0.75f * fRec42[1]));
			fVec9[(IOTA & 4095)] = fTemp70;
			float fTemp71 = (113.0f * fRec37[0]);
			float fTemp72 = (-1.49999499f - fRec30[0]);
			float fTemp73 = (fTemp71 + fTemp72);
			int iTemp74 = int(fTemp73);
			int iTemp75 = std::min<int>(2938, int(std::max<int>(0, int(iTemp74))));
			float fTemp76 = (fRec30[0] + std::floor(fTemp73));
			float fTemp77 = (fTemp71 + (-2.0f - fTemp76));
			float fTemp78 = (0.0f - fTemp77);
			float fTemp79 = (fTemp71 + (-3.0f - fTemp76));
			float fTemp80 = (0.0f - (0.5f * fTemp79));
			float fTemp81 = (fTemp71 + (-1.0f - fTemp76));
			int iTemp82 = std::min<int>(2938, int(std::max<int>(0, int((iTemp74 + 1)))));
			float fTemp83 = (0.0f - fTemp79);
			int iTemp84 = std::min<int>(2938, int(std::max<int>(0, int((iTemp74 + 2)))));
			fRec42[0] = (((fVec9[((IOTA - iTemp75) & 4095)] * fTemp78) * fTemp80) + (fTemp81 * ((fVec9[((IOTA - iTemp82) & 4095)] * fTemp83) + (0.5f * (fTemp77 * fVec9[((IOTA - iTemp84) & 4095)])))));
			float fRec43 = (0.75f * fTemp70);
			float fTemp85 = ((fRec43 + fRec42[1]) - (0.625f * fRec40[1]));
			fVec10[(IOTA & 16383)] = fTemp85;
			float fTemp86 = (fRec30[0] + (397.0f * fRec37[0]));
			float fTemp87 = (fTemp86 + -1.49999499f);
			int iTemp88 = int(fTemp87);
			int iTemp89 = std::min<int>(10322, int(std::max<int>(0, int(iTemp88))));
			float fTemp90 = std::floor(fTemp87);
			float fTemp91 = (fTemp86 + (-2.0f - fTemp90));
			float fTemp92 = (0.0f - fTemp91);
			float fTemp93 = (fTemp86 + (-3.0f - fTemp90));
			float fTemp94 = (0.0f - (0.5f * fTemp93));
			float fTemp95 = (fTemp86 + (-1.0f - fTemp90));
			int iTemp96 = std::min<int>(10322, int(std::max<int>(0, int((iTemp88 + 1)))));
			float fTemp97 = (0.0f - fTemp93);
			int iTemp98 = std::min<int>(10322, int(std::max<int>(0, int((iTemp88 + 2)))));
			fRec40[0] = (((fVec10[((IOTA - iTemp89) & 16383)] * fTemp92) * fTemp94) + (fTemp95 * ((fVec10[((IOTA - iTemp96) & 16383)] * fTemp97) + (0.5f * (fTemp91 * fVec10[((IOTA - iTemp98) & 16383)])))));
			float fRec41 = (0.625f * fTemp85);
			float fTemp99 = ((fRec41 + fRec40[1]) - (0.625f * fRec38[1]));
			fVec11[(IOTA & 8191)] = fTemp99;
			float fTemp100 = (283.0f * fRec37[0]);
			float fTemp101 = (fTemp100 + fTemp72);
			int iTemp102 = int(fTemp101);
			int iTemp103 = std::min<int>(7358, int(std::max<int>(0, int(iTemp102))));
			float fTemp104 = (fRec30[0] + std::floor(fTemp101));
			float fTemp105 = (fTemp100 + (-2.0f - fTemp104));
			float fTemp106 = (0.0f - fTemp105);
			float fTemp107 = (fTemp100 + (-3.0f - fTemp104));
			float fTemp108 = (0.0f - (0.5f * fTemp107));
			float fTemp109 = (fTemp100 + (-1.0f - fTemp104));
			int iTemp110 = std::min<int>(7358, int(std::max<int>(0, int((iTemp102 + 1)))));
			float fTemp111 = (0.0f - fTemp107);
			int iTemp112 = std::min<int>(7358, int(std::max<int>(0, int((iTemp102 + 2)))));
			fRec38[0] = (((fVec11[((IOTA - iTemp103) & 8191)] * fTemp106) * fTemp108) + (fTemp109 * ((fVec11[((IOTA - iTemp110) & 8191)] * fTemp111) + (0.5f * (fTemp105 * fVec11[((IOTA - iTemp112) & 8191)])))));
			float fRec39 = (0.625f * fTemp99);
			float fTemp113 = (fRec39 + fRec38[1]);
			float fTemp114 = (fRec1[1] - (0.75f * fRec55[1]));
			fVec12[(IOTA & 4095)] = fTemp114;
			fRec55[0] = (((fTemp63 * fTemp65) * fVec12[((IOTA - iTemp60) & 4095)]) + (fTemp66 * ((fTemp68 * fVec12[((IOTA - iTemp67) & 4095)]) + (0.5f * (fTemp62 * fVec12[((IOTA - iTemp69) & 4095)])))));
			float fRec56 = (0.75f * fTemp114);
			float fTemp115 = ((fRec56 + fRec55[1]) - (0.75f * fRec53[1]));
			fVec13[(IOTA & 4095)] = fTemp115;
			fRec53[0] = (((fTemp78 * fTemp80) * fVec13[((IOTA - iTemp75) & 4095)]) + (fTemp81 * ((fTemp83 * fVec13[((IOTA - iTemp82) & 4095)]) + (0.5f * (fTemp77 * fVec13[((IOTA - iTemp84) & 4095)])))));
			float fRec54 = (0.75f * fTemp115);
			float fTemp116 = ((fRec54 + fRec53[1]) - (0.625f * fRec51[1]));
			fVec14[(IOTA & 16383)] = fTemp116;
			fRec51[0] = (((fTemp92 * fTemp94) * fVec14[((IOTA - iTemp89) & 16383)]) + (fTemp95 * ((fTemp97 * fVec14[((IOTA - iTemp96) & 16383)]) + (0.5f * (fTemp91 * fVec14[((IOTA - iTemp98) & 16383)])))));
			float fRec52 = (0.625f * fTemp116);
			float fTemp117 = ((fRec52 + fRec51[1]) - (0.625f * fRec49[1]));
			fVec15[(IOTA & 8191)] = fTemp117;
			fRec49[0] = (((fTemp106 * fTemp108) * fVec15[((IOTA - iTemp103) & 8191)]) + (fTemp109 * ((fTemp111 * fVec15[((IOTA - iTemp110) & 8191)]) + (0.5f * (fTemp105 * fVec15[((IOTA - iTemp112) & 8191)])))));
			float fRec50 = (0.625f * fTemp117);
			float fTemp118 = (fRec50 + fRec49[1]);
			float fTemp119 = std::fabs((std::fabs(fTemp113) + std::fabs(fTemp118)));
			float fTemp120 = ((fRec47[1] > fTemp119) ? fConst15 : fConst14);
			fRec48[0] = ((fRec48[1] * fTemp120) + (fTemp119 * (1.0f - fTemp120)));
			fRec47[0] = fRec48[0];
			fRec46[0] = ((fConst12 * fRec46[1]) + (fConst13 * (0.0f - (0.800000012f * std::max<float>(((20.0f * std::log10(fRec47[0])) + 6.0f), 0.0f)))));
			float fTemp121 = std::pow(10.0f, (0.0500000007f * fRec46[0]));
			float fTemp122 = (fRec14[1] + ((fSlow1 * (fTemp113 * fTemp121)) + (fRec15 + (0.699999988f * fRec12[1]))));
			fVec16[(IOTA & 1023)] = fTemp122;
			fRec12[0] = fVec16[((IOTA - 671) & 1023)];
			float fRec13 = (0.0f - (0.699999988f * fTemp122));
			float fTemp123 = (fRec13 + fRec12[1]);
			fVec17[(IOTA & 8191)] = fTemp123;
			fRec11[0] = ((fSlow2 * fRec11[2]) + (fSlow3 * (((6.31716901e-14f * fVec17[((IOTA - 4452) & 8191)]) + fVec17[((IOTA - 4453) & 8191)]) - (6.31716901e-14f * fVec17[((IOTA - 4454) & 8191)]))));
			float fTemp124 = ((fSlow1 * fRec11[0]) - (0.600000024f * fRec7[1]));
			fVec18[(IOTA & 32767)] = fTemp124;
			fRec57[0] = (fSlow10 + (0.999000013f * fRec57[1]));
			float fTemp125 = (fRec30[0] + (1800.0f * fRec57[0]));
			float fTemp126 = (fTemp125 + -1.49999499f);
			int iTemp127 = int(fTemp126);
			float fTemp128 = std::floor(fTemp126);
			float fTemp129 = (fTemp125 + (-2.0f - fTemp128));
			float fTemp130 = (fTemp125 + (-3.0f - fTemp128));
			fRec7[0] = (((fVec18[((IOTA - std::min<int>(18050, int(std::max<int>(0, int(iTemp127))))) & 32767)] * (0.0f - fTemp129)) * (0.0f - (0.5f * fTemp130))) + ((fTemp125 + (-1.0f - fTemp128)) * ((fVec18[((IOTA - std::min<int>(18050, int(std::max<int>(0, int((iTemp127 + 1)))))) & 32767)] * (0.0f - fTemp130)) + (0.5f * (fTemp129 * fVec18[((IOTA - std::min<int>(18050, int(std::max<int>(0, int((iTemp127 + 2)))))) & 32767)])))));
			float fRec8 = (0.600000024f * fTemp124);
			float fTemp131 = (186.915894f * fRec57[0]);
			float fTemp132 = (fTemp131 + -0.499994993f);
			int iTemp133 = int(fTemp132);
			float fTemp134 = std::floor(fTemp132);
			float fTemp135 = (fTemp131 + (-1.0f - fTemp134));
			float fTemp136 = (fTemp131 + (-2.0f - fTemp134));
			float fRec9 = (((fVec18[((IOTA - int(std::min<float>(1872.0f, float(std::max<int>(0, iTemp133))))) & 32767)] * (0.0f - fTemp135)) * (0.0f - (0.5f * fTemp136))) + ((fTemp131 - fTemp134) * ((fVec18[((IOTA - int(std::min<float>(1872.0f, float(std::max<int>(0, (iTemp133 + 1)))))) & 32767)] * (0.0f - fTemp136)) + (0.5f * (fTemp135 * fVec18[((IOTA - int(std::min<float>(1872.0f, float(std::max<int>(0, (iTemp133 + 2)))))) & 32767)])))));
			float fTemp137 = (1232.87671f * fRec57[0]);
			float fTemp138 = (fTemp137 + -0.499994993f);
			int iTemp139 = int(fTemp138);
			float fTemp140 = std::floor(fTemp138);
			float fTemp141 = (fTemp137 + (-1.0f - fTemp140));
			float fTemp142 = (fTemp137 + (-2.0f - fTemp140));
			float fRec10 = (((fVec18[((IOTA - int(std::min<float>(12330.0f, float(std::max<int>(0, iTemp139))))) & 32767)] * (0.0f - fTemp141)) * (0.0f - (0.5f * fTemp142))) + ((fTemp137 - fTemp140) * ((fVec18[((IOTA - int(std::min<float>(12330.0f, float(std::max<int>(0, (iTemp139 + 1)))))) & 32767)] * (0.0f - fTemp142)) + (0.5f * (fTemp141 * fVec18[((IOTA - int(std::min<float>(12330.0f, float(std::max<int>(0, (iTemp139 + 2)))))) & 32767)])))));
			float fTemp143 = (fRec8 + fRec7[1]);
			fVec19[(IOTA & 32767)] = fTemp143;
			float fTemp144 = (fRec30[0] + 3719.5f);
			int iTemp145 = int(fTemp144);
			float fTemp146 = std::floor(fTemp144);
			float fTemp147 = (fRec30[0] + (3719.0f - fTemp146));
			float fTemp148 = (fRec30[0] + (3718.0f - fTemp146));
			fRec1[0] = (fSlow1 * (((fVec19[((IOTA - std::min<int>(18650, int(std::max<int>(0, int(iTemp145))))) & 32767)] * (0.0f - fTemp147)) * (0.0f - (0.5f * fTemp148))) + ((fRec30[0] + (3720.0f - fTemp146)) * ((fVec19[((IOTA - std::min<int>(18650, int(std::max<int>(0, int((iTemp145 + 1)))))) & 32767)] * (0.0f - fTemp148)) + (0.5f * (fTemp147 * fVec19[((IOTA - std::min<int>(18650, int(std::max<int>(0, int((iTemp145 + 2)))))) & 32767)]))))));
			float fTemp149 = float(input0[i]);
			float fTemp150 = std::max<float>(-1.0f, std::min<float>(1.0f, (fTemp149 * fTemp4)));
			float fTemp151 = (fTemp150 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp150))));
			fVec20[(IOTA & 16383)] = fTemp151;
			float fTemp152 = ((fTemp11 * fVec20[((IOTA - iTemp9) & 16383)]) + (fTemp12 * fVec20[((IOTA - iTemp13) & 16383)]));
			fVec21[0] = fTemp152;
			fRec76[0] = (0.0f - (((fTemp2 * fRec76[1]) - (fTemp152 + fVec21[1])) / fTemp15));
			fRec75[0] = (fRec76[0] - (((fTemp16 * fRec75[2]) + (2.0f * (fTemp17 * fRec75[1]))) / fTemp18));
			float fTemp153 = (fRec75[2] + (fRec75[0] + (2.0f * fRec75[1])));
			fVec22[0] = (fTemp153 / fTemp18);
			fRec74[0] = ((fTemp23 * fVec22[1]) - (((fTemp24 * fRec74[1]) - (fTemp153 / fTemp25)) / fTemp22));
			fRec73[0] = (fRec74[0] - (((fTemp26 * fRec73[2]) + (2.0f * (fTemp28 * fRec73[1]))) / fTemp29));
			float fTemp154 = (((((fTemp30 * fRec73[1]) + (fRec73[0] / fTemp27)) + (fRec73[2] / fTemp27)) / fTemp29) - (0.75f * fRec71[1]));
			fVec23[(IOTA & 4095)] = fTemp154;
			float fTemp155 = (fRec30[0] + (151.0f * fRec37[0]));
			float fTemp156 = (fTemp155 + -1.0f);
			int iTemp157 = int(fTemp156);
			float fTemp158 = std::floor(fTemp156);
			fRec71[0] = ((fVec23[((IOTA - std::min<int>(3927, int(std::max<int>(0, int(iTemp157))))) & 4095)] * (fTemp158 + (2.0f - fTemp155))) + ((fTemp155 + (-1.0f - fTemp158)) * fVec23[((IOTA - std::min<int>(3927, int(std::max<int>(0, int((iTemp157 + 1)))))) & 4095)]));
			float fRec72 = (0.75f * fTemp154);
			float fTemp159 = ((fRec72 + fRec71[1]) - (0.75f * fRec69[1]));
			fVec24[(IOTA & 4095)] = fTemp159;
			float fTemp160 = (101.0f * fRec37[0]);
			float fTemp161 = (fTemp160 + fTemp42);
			int iTemp162 = int(fTemp161);
			float fTemp163 = (fRec30[0] + std::floor(fTemp161));
			fRec69[0] = ((fVec24[((IOTA - std::min<int>(2627, int(std::max<int>(0, int(iTemp162))))) & 4095)] * (fTemp163 + (2.0f - fTemp160))) + ((fTemp160 + (-1.0f - fTemp163)) * fVec24[((IOTA - std::min<int>(2627, int(std::max<int>(0, int((iTemp162 + 1)))))) & 4095)]));
			float fRec70 = (0.75f * fTemp159);
			float fTemp164 = ((fRec70 + fRec69[1]) - (0.625f * fRec67[1]));
			fVec25[(IOTA & 16383)] = fTemp164;
			float fTemp165 = (fRec30[0] + (367.0f * fRec37[0]));
			float fTemp166 = (fTemp165 + -1.0f);
			int iTemp167 = int(fTemp166);
			float fTemp168 = std::floor(fTemp166);
			fRec67[0] = ((fVec25[((IOTA - std::min<int>(9543, int(std::max<int>(0, int(iTemp167))))) & 16383)] * (fTemp168 + (2.0f - fTemp165))) + ((fTemp165 + (-1.0f - fTemp168)) * fVec25[((IOTA - std::min<int>(9543, int(std::max<int>(0, int((iTemp167 + 1)))))) & 16383)]));
			float fRec68 = (0.625f * fTemp164);
			float fTemp169 = ((fRec68 + fRec67[1]) - (0.625f * fRec65[1]));
			fVec26[(IOTA & 8191)] = fTemp169;
			float fTemp170 = (281.0f * fRec37[0]);
			float fTemp171 = (fTemp170 + fTemp42);
			int iTemp172 = int(fTemp171);
			float fTemp173 = (fRec30[0] + std::floor(fTemp171));
			fRec65[0] = ((fVec26[((IOTA - std::min<int>(7307, int(std::max<int>(0, int(iTemp172))))) & 8191)] * (fTemp173 + (2.0f - fTemp170))) + ((fTemp170 + (-1.0f - fTemp173)) * fVec26[((IOTA - std::min<int>(7307, int(std::max<int>(0, int((iTemp172 + 1)))))) & 8191)]));
			float fRec66 = (0.625f * fTemp169);
			float fTemp174 = ((fSlow1 * (fTemp118 * fTemp121)) + (fRec65[1] + (fRec66 + (0.699999988f * fRec63[1]))));
			fVec27[(IOTA & 1023)] = fTemp174;
			fRec63[0] = fVec27[((IOTA - 907) & 1023)];
			float fRec64 = (0.0f - (0.699999988f * fTemp174));
			float fTemp175 = (fRec64 + fRec63[1]);
			fVec28[(IOTA & 8191)] = fTemp175;
			fRec62[0] = ((fSlow2 * fRec62[2]) + (fSlow3 * (((6.31716901e-14f * fVec28[((IOTA - 4216) & 8191)]) + fVec28[((IOTA - 4217) & 8191)]) - (6.31716901e-14f * fVec28[((IOTA - 4218) & 8191)]))));
			float fTemp176 = ((fSlow1 * fRec62[0]) - (0.600000024f * fRec58[1]));
			fVec29[(IOTA & 32767)] = fTemp176;
			float fTemp177 = (fRec30[0] + (2656.0f * fRec57[0]));
			float fTemp178 = (fTemp177 + -1.49999499f);
			int iTemp179 = int(fTemp178);
			float fTemp180 = std::floor(fTemp178);
			float fTemp181 = (fTemp177 + (-2.0f - fTemp180));
			float fTemp182 = (fTemp177 + (-3.0f - fTemp180));
			fRec58[0] = (((fVec29[((IOTA - std::min<int>(26610, int(std::max<int>(0, int(iTemp179))))) & 32767)] * (0.0f - fTemp181)) * (0.0f - (0.5f * fTemp182))) + ((fTemp177 + (-1.0f - fTemp180)) * ((fVec29[((IOTA - std::min<int>(26610, int(std::max<int>(0, int((iTemp179 + 1)))))) & 32767)] * (0.0f - fTemp182)) + (0.5f * (fTemp181 * fVec29[((IOTA - std::min<int>(26610, int(std::max<int>(0, int((iTemp179 + 2)))))) & 32767)])))));
			float fRec59 = (0.600000024f * fTemp176);
			float fTemp183 = (334.930634f * fRec57[0]);
			float fTemp184 = (fTemp183 + -0.499994993f);
			int iTemp185 = int(fTemp184);
			float fTemp186 = std::floor(fTemp184);
			float fTemp187 = (fTemp183 + (-1.0f - fTemp186));
			float fTemp188 = (fTemp183 + (-2.0f - fTemp186));
			float fRec60 = (((fVec29[((IOTA - int(std::min<float>(3373.12012f, float(std::max<int>(0, iTemp185))))) & 32767)] * (0.0f - fTemp187)) * (0.0f - (0.5f * fTemp188))) + ((fTemp183 - fTemp186) * ((fVec29[((IOTA - int(std::min<float>(3373.12012f, float(std::max<int>(0, (iTemp185 + 1)))))) & 32767)] * (0.0f - fTemp188)) + (0.5f * (fTemp187 * fVec29[((IOTA - int(std::min<float>(3373.12012f, float(std::max<int>(0, (iTemp185 + 2)))))) & 32767)])))));
			float fTemp189 = (1910.79138f * fRec57[0]);
			float fTemp190 = (fTemp189 + -0.499994993f);
			int iTemp191 = int(fTemp190);
			float fTemp192 = std::floor(fTemp190);
			float fTemp193 = (fTemp189 + (-1.0f - fTemp192));
			float fTemp194 = (fTemp189 + (-2.0f - fTemp192));
			float fRec61 = (((fVec29[((IOTA - int(std::min<float>(19123.1992f, float(std::max<int>(0, iTemp191))))) & 32767)] * (0.0f - fTemp193)) * (0.0f - (0.5f * fTemp194))) + ((fTemp189 - fTemp192) * ((fVec29[((IOTA - int(std::min<float>(19123.1992f, float(std::max<int>(0, (iTemp191 + 1)))))) & 32767)] * (0.0f - fTemp194)) + (0.5f * (fTemp193 * fVec29[((IOTA - int(std::min<float>(19123.1992f, float(std::max<int>(0, (iTemp191 + 2)))))) & 32767)])))));
			float fTemp195 = (fRec59 + fRec58[1]);
			fVec30[(IOTA & 16383)] = fTemp195;
			float fTemp196 = (fRec30[0] + 3162.5f);
			int iTemp197 = int(fTemp196);
			float fTemp198 = std::floor(fTemp196);
			float fTemp199 = (fRec30[0] + (3162.0f - fTemp198));
			float fTemp200 = (fRec30[0] + (3161.0f - fTemp198));
			fRec2[0] = (fSlow1 * (((fVec30[((IOTA - std::min<int>(15865, int(std::max<int>(0, int(iTemp197))))) & 16383)] * (0.0f - fTemp199)) * (0.0f - (0.5f * fTemp200))) + ((fRec30[0] + (3163.0f - fTemp198)) * ((fVec30[((IOTA - std::min<int>(15865, int(std::max<int>(0, int((iTemp197 + 1)))))) & 16383)] * (0.0f - fTemp200)) + (0.5f * (fTemp199 * fVec30[((IOTA - std::min<int>(15865, int(std::max<int>(0, int((iTemp197 + 2)))))) & 16383)]))))));
			float fRec3 = (0.600000024f * (((0.059844356f * fVec17[((IOTA - 1998) & 8191)]) + (0.0439651571f * fVec19[((IOTA - 1067) & 32767)])) - ((0.990509093f * fVec19[((IOTA - 1066) & 32767)]) + (((0.98067528f * fVec17[((IOTA - 1997) & 8191)]) + (fRec9 + (0.0791690946f * fVec17[((IOTA - 1996) & 8191)]))) + (0.0534560457f * fVec19[((IOTA - 1065) & 32767)])))));
			float fRec4 = (0.600000024f * (((0.163035035f * fVec19[((IOTA - 2677) & 32767)]) + (((0.215480208f * fVec17[((IOTA - 3621) & 8191)]) + (((0.982461095f * fVec17[((IOTA - 353) & 8191)]) + (0.0749867484f * fVec17[((IOTA - 354) & 8191)])) + (0.894242823f * fVec17[((IOTA - 3620) & 8191)]))) + (0.932922721f * fVec19[((IOTA - 2676) & 32767)]))) - (((0.109723046f * fVec17[((IOTA - 3619) & 8191)]) + (fRec10 + (0.0574478284f * fVec17[((IOTA - 352) & 8191)]))) + (0.0959577635f * fVec19[((IOTA - 2675) & 32767)]))));
			float fRec5 = (0.600000024f * ((((0.920650661f * fVec28[((IOTA - 2970) & 8191)]) + (((0.996775746f * fVec28[((IOTA - 266) & 8191)]) + (0.0300032832f * fVec28[((IOTA - 267) & 8191)])) + (0.180519745f * fVec28[((IOTA - 2969) & 8191)]))) + (0.00114503212f * fVec30[((IOTA - 120) & 16383)])) - ((0.00115030073f * fVec30[((IOTA - 122) & 16383)]) + (((0.101170406f * fVec28[((IOTA - 2971) & 8191)]) + (fRec61 + (0.02677905f * fVec28[((IOTA - 265) & 8191)]))) + (0.999994755f * fVec30[((IOTA - 121) & 16383)])))));
			float fRec6 = (0.600000024f * (((0.989745259f * fVec30[((IOTA - 2002) & 16383)]) + ((0.125f * fVec28[((IOTA - 2110) & 8191)]) + (0.0557602942f * fVec30[((IOTA - 2001) & 16383)]))) - (((0.75f * fVec28[((IOTA - 2109) & 8191)]) + (fRec60 + (0.375f * fVec28[((IOTA - 2108) & 8191)]))) + (0.0455055274f * fVec30[((IOTA - 2003) & 16383)]))));
			float fTemp201 = (1.0f - fRec0[0]);
			float fTemp202 = ((fRec0[0] * (fRec3 + fRec5)) + (fTemp149 * fTemp201));
			float fTemp203 = ((fRec0[0] * (fRec4 + fRec6)) + (fTemp3 * fTemp201));
			float fTemp204 = std::fabs((std::fabs(fTemp202) + std::fabs(fTemp203)));
			float fTemp205 = ((fRec78[1] > fTemp204) ? fConst12 : fConst18);
			fRec79[0] = ((fRec79[1] * fTemp205) + (fTemp204 * (1.0f - fTemp205)));
			fRec78[0] = fRec79[0];
			fRec77[0] = ((fConst16 * fRec77[1]) + (fConst17 * (0.0f - (0.75f * std::max<float>(((20.0f * std::log10(fRec78[0])) + 6.0f), 0.0f)))));
			float fTemp206 = std::pow(10.0f, (0.0500000007f * fRec77[0]));
			output0[i] = FAUSTFLOAT((fTemp202 * fTemp206));
			output1[i] = FAUSTFLOAT((fTemp203 * fTemp206));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			IOTA = (IOTA + 1);
			fRec28[1] = fRec28[0];
			fVec2[1] = fVec2[0];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fVec3[1] = fVec3[0];
			fRec29[1] = fRec29[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			iRec36[1] = iRec36[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec37[1] = fRec37[0];
			fRec20[1] = fRec20[0];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec14[1] = fRec14[0];
			fRec44[1] = fRec44[0];
			fRec42[1] = fRec42[0];
			fRec40[1] = fRec40[0];
			fRec38[1] = fRec38[0];
			fRec55[1] = fRec55[0];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec57[1] = fRec57[0];
			fRec7[1] = fRec7[0];
			fRec1[1] = fRec1[0];
			fVec21[1] = fVec21[0];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fVec22[1] = fVec22[0];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec71[1] = fRec71[0];
			fRec69[1] = fRec69[0];
			fRec67[1] = fRec67[0];
			fRec65[1] = fRec65[0];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec58[1] = fRec58[0];
			fRec2[1] = fRec2[0];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			fRec77[1] = fRec77[0];
		}
	}

};

#endif
