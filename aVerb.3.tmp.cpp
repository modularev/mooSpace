/* ------------------------------------------------------------
name: "aVerb.3.tmp"
Code generated with Faust 2.23.4 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>


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
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec7[2];
	FAUSTFLOAT fHslider2;
	int IOTA;
	float fVec0[16384];
	FAUSTFLOAT fHslider3;
	float fRec31[3];
	float fVec1[8192];
	FAUSTFLOAT fHslider4;
	float fRec32[2];
	float fRec30[3];
	float fRec28[2];
	float fVec2[4096];
	float fRec27[3];
	float fRec25[2];
	float fVec3[16384];
	float fRec24[3];
	float fRec22[2];
	float fVec4[16384];
	float fRec21[3];
	float fRec19[2];
	float fVec5[1024];
	float fRec18[3];
	float fRec16[2];
	float fVec6[8192];
	float fRec15[3];
	float fRec14[3];
	float fVec7[2048];
	float fRec13[3];
	float fRec9[2];
	float fRec33[3];
	float fRec34[3];
	float fVec8[4096];
	float fRec8[3];
	float fRec1[2];
	float fVec9[1024];
	float fRec45[3];
	float fRec43[2];
	float fVec10[8192];
	float fRec42[3];
	float fRec41[3];
	float fVec11[4096];
	float fRec40[3];
	float fRec36[2];
	float fRec46[3];
	float fRec47[3];
	float fVec12[4096];
	float fRec35[3];
	float fRec2[2];
	float fRec48[3];
	float fRec49[3];
	float fRec50[3];
	float fRec51[3];
	float fRec52[3];
	float fRec53[3];
	float fRec54[3];
	float fRec55[3];
	float fRec56[3];
	float fRec57[3];
	int fSampleRate;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "aVerb.3.tmp.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.2");
		m->declare("name", "aVerb.3.tmp");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
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
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.20000000000000001f);
		fHslider3 = FAUSTFLOAT(10.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec7[l1] = 0.0f;
		}
		IOTA = 0;
		for (int l2 = 0; (l2 < 16384); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec31[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 8192); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec32[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec30[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec28[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			fVec2[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec27[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec25[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 16384); l11 = (l11 + 1)) {
			fVec3[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec24[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec22[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 16384); l14 = (l14 + 1)) {
			fVec4[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec21[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec19[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 1024); l17 = (l17 + 1)) {
			fVec5[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
			fRec18[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec16[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 8192); l20 = (l20 + 1)) {
			fVec6[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec15[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec14[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2048); l23 = (l23 + 1)) {
			fVec7[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec13[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec9[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec33[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec34[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			fVec8[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec8[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec1[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 1024); l31 = (l31 + 1)) {
			fVec9[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec45[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec43[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 8192); l34 = (l34 + 1)) {
			fVec10[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec42[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec41[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			fVec11[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec40[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec36[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec46[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec47[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 4096); l42 = (l42 + 1)) {
			fVec12[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec35[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec2[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec48[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec49[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec50[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec51[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec52[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec53[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec54[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec55[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec56[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec57[l54] = 0.0f;
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
		ui_interface->openVerticalBox("aVerb.3.tmp");
		ui_interface->addHorizontalSlider("Brightness", &fHslider2, 0.200000003f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Input Diffusion", &fHslider4, 1.0f, 0.100000001f, 25.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Pre-delay", &fHslider3, 10.0f, 0.100000001f, 300.0f, 1.0f);
		ui_interface->addHorizontalSlider("Room Size", &fHslider1, 0.5f, 0.00100000005f, 0.999000013f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Wet/Dry", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = float(fHslider2);
		float fSlow3 = (1.0f - fSlow2);
		int iSlow4 = int((44.0999985f * float(fHslider3)));
		float fSlow5 = (0.00100000005f * float(fHslider4));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec7[0] = (fSlow1 + (0.999000013f * fRec7[1]));
			float fTemp0 = float(input0[i]);
			float fTemp1 = float(input1[i]);
			fVec0[(IOTA & 16383)] = (fTemp0 + fTemp1);
			fRec31[0] = ((0.000500000024f * fRec31[2]) + (0.499749988f * fVec0[((IOTA - iSlow4) & 16383)]));
			float fTemp2 = (fRec31[0] - (0.75f * fRec28[1]));
			fVec1[(IOTA & 8191)] = fTemp2;
			fRec32[0] = (fSlow5 + (0.999000013f * fRec32[1]));
			float fTemp3 = (142.0f * fRec32[0]);
			float fTemp4 = (fTemp3 + -2.49998999f);
			float fTemp5 = std::floor(fTemp4);
			float fTemp6 = (fTemp5 + (3.0f - fTemp3));
			float fTemp7 = (fTemp5 + (2.0f - fTemp3));
			float fTemp8 = (fTemp3 + (1.0f - fTemp5));
			float fTemp9 = (2.0f * fRec30[1]);
			float fTemp10 = (fTemp3 - fTemp5);
			fRec30[0] = (fVec1[((IOTA - std::min<int>(4260, std::max<int>(0, int(fTemp4)))) & 8191)] - ((fTemp6 * (((fRec30[2] * fTemp7) / fTemp8) + fTemp9)) / fTemp10));
			fRec28[0] = (fRec30[2] + ((fTemp6 * (fTemp9 + ((fRec30[0] * fTemp7) / fTemp8))) / fTemp10));
			float fRec29 = (0.75f * fTemp2);
			float fTemp11 = ((fRec29 + fRec28[1]) - (0.75f * fRec25[1]));
			fVec2[(IOTA & 4095)] = fTemp11;
			float fTemp12 = (107.0f * fRec32[0]);
			float fTemp13 = (fTemp12 + -2.49998999f);
			float fTemp14 = std::floor(fTemp13);
			float fTemp15 = (fTemp14 + (3.0f - fTemp12));
			float fTemp16 = (fTemp14 + (2.0f - fTemp12));
			float fTemp17 = (fTemp12 + (1.0f - fTemp14));
			float fTemp18 = (2.0f * fRec27[1]);
			float fTemp19 = (fTemp12 - fTemp14);
			fRec27[0] = (fVec2[((IOTA - std::min<int>(3210, std::max<int>(0, int(fTemp13)))) & 4095)] - ((fTemp15 * (((fRec27[2] * fTemp16) / fTemp17) + fTemp18)) / fTemp19));
			fRec25[0] = (fRec27[2] + ((fTemp15 * (fTemp18 + ((fRec27[0] * fTemp16) / fTemp17))) / fTemp19));
			float fRec26 = (0.75f * fTemp11);
			float fTemp20 = ((fRec26 + fRec25[1]) - (0.625f * fRec22[1]));
			fVec3[(IOTA & 16383)] = fTemp20;
			float fTemp21 = (379.0f * fRec32[0]);
			float fTemp22 = (fTemp21 + -2.49998999f);
			float fTemp23 = std::floor(fTemp22);
			float fTemp24 = (fTemp23 + (3.0f - fTemp21));
			float fTemp25 = (fTemp23 + (2.0f - fTemp21));
			float fTemp26 = (fTemp21 + (1.0f - fTemp23));
			float fTemp27 = (2.0f * fRec24[1]);
			float fTemp28 = (fTemp21 - fTemp23);
			fRec24[0] = (fVec3[((IOTA - std::min<int>(11370, std::max<int>(0, int(fTemp22)))) & 16383)] - ((fTemp24 * (((fRec24[2] * fTemp25) / fTemp26) + fTemp27)) / fTemp28));
			fRec22[0] = (fRec24[2] + ((fTemp24 * (fTemp27 + ((fRec24[0] * fTemp25) / fTemp26))) / fTemp28));
			float fRec23 = (0.625f * fTemp20);
			float fTemp29 = ((fRec23 + fRec22[1]) - (0.625f * fRec19[1]));
			fVec4[(IOTA & 16383)] = fTemp29;
			float fTemp30 = (277.0f * fRec32[0]);
			float fTemp31 = (fTemp30 + -2.49998999f);
			float fTemp32 = std::floor(fTemp31);
			float fTemp33 = (fTemp32 + (3.0f - fTemp30));
			float fTemp34 = (fTemp32 + (2.0f - fTemp30));
			float fTemp35 = (fTemp30 + (1.0f - fTemp32));
			float fTemp36 = (2.0f * fRec21[1]);
			float fTemp37 = (fTemp30 - fTemp32);
			fRec21[0] = (fVec4[((IOTA - std::min<int>(8310, std::max<int>(0, int(fTemp31)))) & 16383)] - ((fTemp33 * (((fRec21[2] * fTemp34) / fTemp35) + fTemp36)) / fTemp37));
			fRec19[0] = (fRec21[2] + ((fTemp33 * (fTemp36 + ((fRec21[0] * fTemp34) / fTemp35))) / fTemp37));
			float fRec20 = (0.625f * fTemp29);
			float fTemp38 = (fRec19[1] + ((fRec7[0] * fRec2[1]) + (fRec20 + (0.699999988f * fRec16[1]))));
			fVec5[(IOTA & 1023)] = fTemp38;
			float fTemp39 = (1.687539e-14f * fRec18[1]);
			fRec18[0] = ((fVec5[((IOTA - 669) & 1023)] + (2.10942375e-15f * fRec18[2])) - fTemp39);
			fRec16[0] = ((fTemp39 + fRec18[2]) - (2.10942375e-15f * fRec18[0]));
			float fRec17 = (0.0f - (0.699999988f * fTemp38));
			float fTemp40 = (fRec17 + fRec16[1]);
			fVec6[(IOTA & 8191)] = fTemp40;
			float fTemp41 = (1.68457845e-13f * fRec15[1]);
			fRec15[0] = ((fVec6[((IOTA - 4451) & 8191)] + (2.10572306e-14f * fRec15[2])) - fTemp41);
			fRec14[0] = ((fSlow2 * fRec14[2]) + (fSlow3 * ((fTemp41 + fRec15[2]) - (2.10572306e-14f * fRec15[0]))));
			float fTemp42 = ((fRec7[0] * fRec14[0]) - (0.5f * fRec9[1]));
			fVec7[(IOTA & 2047)] = fTemp42;
			float fTemp43 = (1.687539e-14f * fRec13[1]);
			fRec13[0] = ((fVec7[((IOTA - 1797) & 2047)] + (2.10942375e-15f * fRec13[2])) - fTemp43);
			fRec9[0] = ((fTemp43 + fRec13[2]) - (2.10942375e-15f * fRec13[0]));
			float fRec10 = (0.5f * fTemp42);
			float fTemp44 = (0.057692308f * fRec33[1]);
			fRec33[0] = ((fVec7[((IOTA - 185) & 2047)] + (0.00674683321f * fRec33[2])) - fTemp44);
			float fRec11 = ((fTemp44 + fRec33[2]) - (0.00674683321f * fRec33[0]));
			float fTemp45 = (0.0857142881f * fRec34[1]);
			fRec34[0] = ((fVec7[((IOTA - 1231) & 2047)] + (0.00969207473f * fRec34[2])) - fTemp45);
			float fRec12 = ((fTemp45 + fRec34[2]) - (0.00969207473f * fRec34[0]));
			float fTemp46 = (fRec10 + fRec9[1]);
			fVec8[(IOTA & 4095)] = fTemp46;
			float fTemp47 = (1.34707065e-13f * fRec8[1]);
			fRec8[0] = ((fVec8[((IOTA - 3718) & 4095)] + fTemp47) - (1.68383831e-14f * fRec8[2]));
			fRec1[0] = (fRec7[0] * ((fRec8[2] + (1.68383831e-14f * fRec8[0])) - fTemp47));
			float fTemp48 = ((fRec7[0] * fRec1[1]) + ((fRec20 + fRec19[1]) + (0.699999988f * fRec43[1])));
			fVec9[(IOTA & 1023)] = fTemp48;
			float fTemp49 = (1.687539e-14f * fRec45[1]);
			fRec45[0] = ((fVec9[((IOTA - 905) & 1023)] + (2.10942375e-15f * fRec45[2])) - fTemp49);
			fRec43[0] = ((fTemp49 + fRec45[2]) - (2.10942375e-15f * fRec45[0]));
			float fRec44 = (0.0f - (0.699999988f * fTemp48));
			float fTemp50 = (fRec44 + fRec43[1]);
			fVec10[(IOTA & 8191)] = fTemp50;
			float fTemp51 = (1.68457845e-13f * fRec42[1]);
			fRec42[0] = ((fVec10[((IOTA - 4215) & 8191)] + (2.10572306e-14f * fRec42[2])) - fTemp51);
			fRec41[0] = ((fSlow2 * fRec41[2]) + (fSlow3 * ((fTemp51 + fRec42[2]) - (2.10572306e-14f * fRec42[0]))));
			float fTemp52 = ((fRec7[0] * fRec41[0]) - (0.5f * fRec36[1]));
			fVec11[(IOTA & 4095)] = fTemp52;
			float fTemp53 = (1.34707065e-13f * fRec40[1]);
			fRec40[0] = ((fVec11[((IOTA - 2653) & 4095)] + fTemp53) - (1.68383831e-14f * fRec40[2]));
			fRec36[0] = ((fRec40[2] + (1.68383831e-14f * fRec40[0])) - fTemp53);
			float fRec37 = (0.5f * fTemp52);
			float fTemp54 = (0.0473321863f * fRec46[1]);
			fRec46[0] = ((fVec11[((IOTA - 333) & 4095)] + (0.00560332881f * fRec46[2])) - fTemp54);
			float fRec38 = ((fTemp54 + fRec46[2]) - (0.00560332881f * fRec46[0]));
			float fTemp55 = (0.14948453f * fRec47[1]);
			fRec47[0] = ((fVec11[((IOTA - 1909) & 4095)] + (0.0156008527f * fRec47[2])) - fTemp55);
			float fRec39 = ((fTemp55 + fRec47[2]) - (0.0156008527f * fRec47[0]));
			float fTemp56 = (fRec37 + fRec36[1]);
			fVec12[(IOTA & 4095)] = fTemp56;
			float fTemp57 = (1.34707065e-13f * fRec35[1]);
			fRec35[0] = ((fVec12[((IOTA - 3161) & 4095)] + fTemp57) - (1.68383831e-14f * fRec35[2]));
			fRec2[0] = (fRec7[0] * ((fRec35[2] + (1.68383831e-14f * fRec35[0])) - fTemp57));
			float fTemp58 = (0.0971786827f * fRec48[1]);
			fRec48[0] = ((fVec6[((IOTA - 1995) & 8191)] + (0.0108352536f * fRec48[2])) - fTemp58);
			float fTemp59 = (0.067127347f * fRec49[1]);
			fRec49[0] = ((fVec8[((IOTA - 1064) & 4095)] + (0.00776252337f * fRec49[2])) - fTemp59);
			float fRec3 = (0.600000024f * (((0.0108352536f * fRec48[0]) + (0.00776252337f * fRec49[0])) - (fRec11 + (fRec49[2] + ((fTemp58 + fRec48[2]) + fTemp59)))));
			float fTemp60 = (0.158940405f * fRec50[1]);
			fRec50[0] = ((fVec8[((IOTA - 2674) & 4095)] + fTemp60) - (0.0234920345f * fRec50[2]));
			float fTemp61 = (0.19559902f * fRec51[1]);
			fRec51[0] = ((fVec6[((IOTA - 3618) & 8191)] + fTemp61) - (0.0299648885f * fRec51[2]));
			float fTemp62 = (0.0845569596f * fRec52[1]);
			fRec52[0] = ((fVec6[((IOTA - 351) & 8191)] + fTemp62) - (0.011585813f * fRec52[2]));
			float fRec4 = (0.600000024f * (((0.0234920345f * fRec50[0]) + ((0.0299648885f * fRec51[0]) + ((0.011585813f * fRec52[0]) + ((fRec52[2] + fRec51[2]) + fRec50[2])))) - (fRec12 + ((fTemp62 + fTemp61) + fTemp60))));
			float fTemp63 = (0.0371517017f * fRec53[1]);
			fRec53[0] = ((fVec10[((IOTA - 264) & 8191)] + fTemp63) - (0.00483896583f * fRec53[2]));
			float fTemp64 = (0.207253888f * fRec54[1]);
			fRec54[0] = ((fVec10[((IOTA - 2968) & 8191)] + (0.0200188421f * fRec54[2])) - fTemp64);
			float fTemp65 = (0.00152905204f * fRec55[1]);
			fRec55[0] = ((fVec12[((IOTA - 119) & 4095)] + fTemp65) - (0.000191460349f * fRec55[2]));
			float fRec5 = (0.600000024f * (((0.00483896583f * fRec53[0]) + ((fRec54[2] + (fRec53[2] + fTemp64)) + fTemp65)) - ((0.000191460349f * fRec55[0]) + ((0.0200188421f * fRec54[0]) + (fRec39 + (fTemp63 + fRec55[2]))))));
			float fTemp66 = (0.400000006f * fRec56[1]);
			fRec56[0] = ((fVec10[((IOTA - 2107) & 8191)] + (0.0285714287f * fRec56[2])) - fTemp66);
			float fTemp67 = (0.0698689967f * fRec57[1]);
			fRec57[0] = ((fVec12[((IOTA - 2000) & 4095)] + (0.00805308204f * fRec57[2])) - fTemp67);
			float fRec6 = (0.600000024f * (((0.0285714287f * fRec56[0]) + (fTemp67 + fRec57[2])) - ((fRec38 + (fTemp66 + fRec56[2])) + (0.00805308204f * fRec57[0]))));
			float fTemp68 = (1.0f - fRec0[0]);
			output0[i] = FAUSTFLOAT(((fRec0[0] * (fRec3 + fRec5)) + (fTemp0 * fTemp68)));
			output1[i] = FAUSTFLOAT(((fRec0[0] * (fRec4 + fRec6)) + (fTemp1 * fTemp68)));
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
			IOTA = (IOTA + 1);
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec9[1] = fRec9[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec1[1] = fRec1[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec36[1] = fRec36[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec2[1] = fRec2[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
		}
	}

};

#endif
