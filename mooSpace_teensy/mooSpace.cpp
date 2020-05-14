/* ------------------------------------------------------------
author: "Arev Imer (arev.imer@students.fhnw.ch)"
copyright: "Arev"
name: "mooSpace"
version: "0.1"
Code generated with Faust 2.23.10 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************/

#include "mooSpace.h"

// IMPORTANT: in order for MapUI to work, the teensy linker must be g++
/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            do {
                if ((*it).second == zone) return (*it).first;
            }
            while (it++ != fPathZoneMap.end());
            return "";
        }
    
        static bool endsWith(std::string const& str, std::string const& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/

// MIDI support
#if MIDICTRL
/************************** BEGIN MidiUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <cmath>

/************************** BEGIN GUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
                            (GRAME, Copyright 2015-2019)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) = 0;
        virtual double faust2ui(double x) = 0;
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};


//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>

/************************** BEGIN SimpleParser.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double min;
    double max;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), min(0.), max(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    std::stringstream reader(p);
    std::streambuf* pbuf = reader.rdbuf();
    
    // Keep position before parsing
    std::streamsize size1 = pbuf->in_avail();
    
    // Parse the number
    reader >> x;
    
    // Keep position after parsing
    std::streamsize size2 = pbuf->in_avail();
    
    // Move from the actual size
    p += (size1 - size2);
    
    // True if the number contains at least one digit
    return (size1 > size2);
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    // single quoted
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { std::cerr << "parseMenuList2 : (" << saved << ") is not a valid list !\n"; }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].min = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].max = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H
/**************************  END  SimpleParser.h **************************/

static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        std::cerr << "ERROR unrecognized state " << state << std::endl;
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    virtual double cache() = 0;
    virtual void reflectZone() = 0;
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
        
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            for (auto& it : fZoneMap) {
                delete it.second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
 
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        static void runAllGuis()
        {
            for (auto& g : fGuiList) {
                g->run();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        virtual void show() {};	
        virtual bool run() { return false; };

        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition
 */

template <typename REAL>
class uiTypedItem : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItem(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItem()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItem<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItem<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * Base class for items with a converter
 */

struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code
 */

class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item
 */

class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control
 */

struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items
 */

class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                std::cerr << "ringbuffer_write error DatedControl" << std::endl;
            }
        }
    
};

/**
 * Allows to group a set of zones
 */

class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            for (auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Can not be defined as method in the classes

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (auto& it : *cl) {
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>


/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        int fDSPSize;                   // In bytes
        std::map<std::string, int> fPathTable;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            popLabel();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const std::map<std::string, int>& path_table):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/*************************************
 A time-stamped short MIDI message
**************************************/

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/*******************************************************************************
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 *******************************************************************************/

class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 127)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/*
 A class to decode NRPN and RPN messages, adapted from JUCE forum message: https://forum.juce.com/t/14bit-midi-controller-support/11517
*/

class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};


/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

//-------------------------------
// For timestamped MIDI messages
//-------------------------------

struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/*****************************************************************************
* Helper code for MIDI meta and polyphonic 'nvoices' parsing
******************************************************************************/

struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data is handled.
 ******************************************************************************/

class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        int rangeChan() { return (((fChan < 0) || (fChan > 15)) ? 0 : fChan); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = -1):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/*****************************************************************************
 * Base class for MIDI aware UI items
 ******************************************************************************/

class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/*****************************************************************************
 * Base class for MIDI aware UI items with timestamp support
 ******************************************************************************/

class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

//-----------
// MIDI sync
//-----------

class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem {
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem {

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

//----------------------
// Standard MIDI events
//----------------------

class uiMidiProgChange : public uiMidiTimedItem {
    
    private:
        
        int fPgm;
  
    public:
    
        uiMidiProgChange(midi* midi_out, int pgm, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fPgm(pgm)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->progChange(rangeChan(), fPgm);
            }
        }
        
};

class uiMidiChanPress : public uiMidiTimedItem {
    
    private:
        
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, int press, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fPress(press)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->chanPress(rangeChan(), fPress);
            }
        }
        
};

//------------------------------------------------------
// uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping
//------------------------------------------------------

class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(rangeChan(), fCtrl, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true, int chan = -1)
        :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->pitchWheel(rangeChan(), fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

//--------------------------------------------------------------
// uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity
//--------------------------------------------------------------

class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(rangeChan(), fKeyOn, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//--------------------------------------------------------------
// uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity
//--------------------------------------------------------------

class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOff(rangeChan(), fKeyOff, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//----------------------------------------------------------------
// uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity
//----------------------------------------------------------------

class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(rangeChan(), fKey, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::map <int, std::vector<uiMidiProgChange*> > TProgChangeTable;
    typedef std::map <int, std::vector<uiMidiChanPress*> >  TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u %u", &num, &chan) == 2) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &num) == 1) {
                            fProgChangeTable[num].push_back(new uiMidiProgChange(fMidiHandler, num, this, zone, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u %u", &num, &chan) == 2) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input, chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &num) == 1) {
                            fChanPressTable[num].push_back(new uiMidiChanPress(fMidiHandler, num, this, zone, input));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                if (channel_aux == -1 || channel == channel_aux) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        { 
            fMidiHandler->removeMidiIn(this);
            if (fDelete) delete fMidiHandler;
        }
    
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable2<TProgChangeTable>(fProgChangeTable, date, channel, pgm, FAUSTFLOAT(1));
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable2<TChanPressTable>(fChanPressTable, date, channel, press, FAUSTFLOAT(1));
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN teensy-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __teensy_midi__
#define __teensy_midi__

#include <iostream>
#include <cstdlib>

#include "Arduino.h"

extern usb_midi_class gUSBMIDI;

class teensy_midi : public midi_handler {
    
    public:
        
        void processMidi()
        {
            while (gUSBMIDI.read()) {
                
                int type = gUSBMIDI.getType();       // which MIDI message, 128-255
                int channel = gUSBMIDI.getChannel(); // which MIDI channel, 0-15
                double time = (double)gUSBMIDI.Clock;
                
                switch(type) {
                    case gUSBMIDI.Clock:
                        handleClock(time);
                        break;
                    case usbMIDI.Start:
                    // We can consider start and continue as identical messages
                    case usbMIDI.Continue:
                        handleStart(time);
                        break;
                    case gUSBMIDI.Stop:
                        handleStop(time);
                        break;
                    case gUSBMIDI.ProgramChange:
                        handleProgChange(time, channel, gUSBMIDI.getData1());
                        break;
                    case gUSBMIDI.AfterTouchChannel:
                        handleAfterTouch(time, channel, gUSBMIDI.getData1());
                        break;
                    case gUSBMIDI.NoteOff:
                        handleKeyOff(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.NoteOn:
                        handleKeyOn(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.ControlChange:
                        handleCtrlChange(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.PitchBend:
                        handlePitchWheel(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.AfterTouchPoly:
                        handlePolyAfterTouch(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                }
            }
        }
};

#endif
/**************************  END  teensy-midi.h **************************/
#endif

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)


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
	
 public:
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec12[2];
	FAUSTFLOAT fHslider3;
	float fRec27[2];
	int IOTA;
	float fVec1[16384];
	FAUSTFLOAT fHslider4;
	float fRec28[2];
	float fVec2[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider5;
	float fRec29[2];
	float fRec26[2];
	float fRec25[3];
	float fVec3[2];
	FAUSTFLOAT fHslider6;
	float fRec30[2];
	float fRec24[2];
	float fRec23[3];
	float fVec4[2048];
	FAUSTFLOAT fHslider7;
	float fRec31[2];
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fRec35[2];
	float fRec36[2];
	int iRec37[2];
	float fRec34[2];
	float fConst9;
	float fRec33[2];
	float fConst10;
	float fConst11;
	float fRec32[3];
	FAUSTFLOAT fHslider8;
	float fRec38[2];
	float fRec21[2];
	float fVec5[1024];
	float fRec19[2];
	float fVec6[4096];
	float fRec17[2];
	float fVec7[4096];
	float fRec15[2];
	float fVec8[2048];
	float fRec45[2];
	float fVec9[1024];
	float fRec43[2];
	float fVec10[4096];
	float fRec41[2];
	float fVec11[4096];
	float fRec39[2];
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec49[2];
	float fRec48[2];
	float fRec47[2];
	float fVec12[4096];
	FAUSTFLOAT fHslider9;
	float fRec50[2];
	float fRec13[2];
	float fVec13[8192];
	float fRec11[3];
	float fVec14[16384];
	float fRec7[2];
	float fVec15[4096];
	float fRec1[2];
	float fVec16[2048];
	float fRec64[2];
	float fVec17[2048];
	float fRec62[2];
	float fVec18[4096];
	float fRec60[2];
	float fVec19[4096];
	float fRec58[2];
	float fRec68[2];
	float fRec67[2];
	float fRec66[2];
	float fVec20[8192];
	float fRec56[2];
	float fVec21[8192];
	float fRec55[3];
	float fVec22[16384];
	float fRec51[2];
	float fVec23[4096];
	float fRec2[2];
	float fConst16;
	float fConst17;
	float fConst18;
	float fRec71[2];
	float fRec70[2];
	float fRec69[2];
	
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
		m->declare("filename", "mooSpace.dsp");
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
		fConst2 = std::tan((15.707963f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 1.0f) / fConst2) + 1.0f));
		fConst5 = (1.0f / (fConst3 + 1.0f));
		fConst6 = (31.415926f / fConst0);
		fConst7 = std::sin(fConst6);
		fConst8 = std::cos(fConst6);
		fConst9 = (1.0f - fConst3);
		fConst10 = (((fConst3 + -1.0f) / fConst2) + 1.0f);
		fConst11 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst2))));
		fConst12 = std::exp((0.0f - (4.0f / fConst0)));
		fConst13 = (1.0f - fConst12);
		fConst14 = std::exp((0.0f - (2.0f / fConst0)));
		fConst15 = std::exp((0.0f - (1.0f / fConst0)));
		fConst16 = std::exp((0.0f - (2500.0f / fConst0)));
		fConst17 = (1.0f - fConst16);
		fConst18 = std::exp((0.0f - (1250.0f / fConst0)));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.29999999999999999f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.02f);
		fHslider8 = FAUSTFLOAT(0.5f);
		fHslider9 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec12[l2] = 0.0f;
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
			fRec29[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec26[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
			fRec25[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec30[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec24[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec23[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fVec4[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec31[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec35[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec36[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			iRec37[l18] = 0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec34[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec33[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec32[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec38[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 1024); l24 = (l24 + 1)) {
			fVec5[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 4096); l26 = (l26 + 1)) {
			fVec6[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec17[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			fVec7[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec15[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 2048); l30 = (l30 + 1)) {
			fVec8[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec45[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 1024); l32 = (l32 + 1)) {
			fVec9[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec43[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			fVec10[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec41[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 4096); l36 = (l36 + 1)) {
			fVec11[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec39[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec49[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec48[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec47[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 4096); l41 = (l41 + 1)) {
			fVec12[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec50[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec13[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 8192); l44 = (l44 + 1)) {
			fVec13[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec11[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 16384); l46 = (l46 + 1)) {
			fVec14[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec7[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			fVec15[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec1[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 2048); l50 = (l50 + 1)) {
			fVec16[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec64[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 2048); l52 = (l52 + 1)) {
			fVec17[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec62[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 4096); l54 = (l54 + 1)) {
			fVec18[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec60[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 4096); l56 = (l56 + 1)) {
			fVec19[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec58[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec68[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec67[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec66[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 8192); l61 = (l61 + 1)) {
			fVec20[l61] = 0.0f;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec56[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 8192); l63 = (l63 + 1)) {
			fVec21[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec55[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 16384); l65 = (l65 + 1)) {
			fVec22[l65] = 0.0f;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec51[l66] = 0.0f;
		}
		for (int l67 = 0; (l67 < 4096); l67 = (l67 + 1)) {
			fVec23[l67] = 0.0f;
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec2[l68] = 0.0f;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec71[l69] = 0.0f;
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec70[l70] = 0.0f;
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec69[l71] = 0.0f;
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
		ui_interface->addHorizontalSlider("High Cut", &fHslider5, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Low Cut", &fHslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("colour", &fHslider2, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("decay", &fHslider1, 0.300000012f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("drag", &fHslider9, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("lag", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("mix", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("modulate", &fHslider7, 0.0199999996f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("push", &fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("smear", &fHslider8, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = std::sqrt(float(fHslider1));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = (0.00100000005f * float(fHslider3));
		float fSlow4 = (15.9989996f * float(fHslider4));
		float fSlow5 = (0.00100000005f * ((14980.0f * mydsp_faustpower2_f(float(fHslider5))) + 20.0f));
		float fSlow6 = (0.00100000005f * ((4980.0f * mydsp_faustpower2_f(float(fHslider6))) + 20.0f));
		float fSlow7 = (0.150000006f * float(fHslider7));
		float fSlow8 = (0.00949999969f * float(fHslider8));
		float fSlow9 = (0.00499999989f * float(fHslider9));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			fRec12[0] = (fSlow2 + (0.999000013f * fRec12[1]));
			float fTemp0 = (1.0f - fRec12[0]);
			fRec27[0] = (fSlow3 + (0.999000013f * fRec27[1]));
			float fTemp1 = std::pow(10.0f, (2.0f * fRec27[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (float(input0[i]) * fTemp1)));
			float fTemp3 = (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp2)));
			float fTemp4 = std::max<float>(-1.0f, std::min<float>(1.0f, (float(input1[i]) * fTemp1)));
			float fTemp5 = (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp4)));
			float fTemp6 = ((fTemp2 * fTemp3) + (fTemp4 * fTemp5));
			fVec1[(IOTA & 16383)] = fTemp6;
			fRec28[0] = (fSlow4 + (0.999000013f * fRec28[1]));
			int iTemp7 = int(fRec28[0]);
			float fTemp8 = std::floor(fRec28[0]);
			float fTemp9 = ((fVec1[((IOTA - std::min<int>(16001, std::max<int>(0, iTemp7))) & 16383)] * (fTemp8 + (1.0f - fRec28[0]))) + ((fRec28[0] - fTemp8) * fVec1[((IOTA - std::min<int>(16001, std::max<int>(0, (iTemp7 + 1)))) & 16383)]));
			fVec2[0] = fTemp9;
			fRec29[0] = (fSlow5 + (0.999000013f * fRec29[1]));
			float fTemp10 = std::tan((fConst1 * fRec29[0]));
			float fTemp11 = (1.0f / fTemp10);
			fRec26[0] = (((0.5f * (fTemp9 + fVec2[1])) - (fRec26[1] * (1.0f - fTemp11))) / (fTemp11 + 1.0f));
			float fTemp12 = (((fTemp11 + 1.0f) / fTemp10) + 1.0f);
			fRec25[0] = (fRec26[0] - (((fRec25[2] * (((fTemp11 + -1.0f) / fTemp10) + 1.0f)) + (2.0f * (fRec25[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp10)))))) / fTemp12));
			float fTemp13 = (fRec25[2] + (fRec25[0] + (2.0f * fRec25[1])));
			fVec3[0] = (fTemp13 / fTemp12);
			fRec30[0] = (fSlow6 + (0.999000013f * fRec30[1]));
			float fTemp14 = std::tan((fConst1 * fRec30[0]));
			float fTemp15 = (1.0f / fTemp14);
			float fTemp16 = (fTemp15 + 1.0f);
			fRec24[0] = ((fVec3[1] * (0.0f - (1.0f / (fTemp14 * fTemp16)))) + (((fTemp13 / (fTemp14 * fTemp12)) - (fRec24[1] * (1.0f - fTemp15))) / fTemp16));
			float fTemp17 = mydsp_faustpower2_f(fTemp14);
			float fTemp18 = (((fTemp15 + 1.0f) / fTemp14) + 1.0f);
			fRec23[0] = (fRec24[0] - (((fRec23[2] * (((fTemp15 + -1.0f) / fTemp14) + 1.0f)) + (2.0f * (fRec23[1] * (1.0f - (1.0f / fTemp17))))) / fTemp18));
			float fTemp19 = (((((fRec23[1] * (0.0f - (2.0f / fTemp17))) + (fRec23[0] / fTemp17)) + (fRec23[2] / fTemp17)) / fTemp18) - (0.75f * fRec21[1]));
			fVec4[(IOTA & 2047)] = fTemp19;
			fRec31[0] = (fSlow7 + (0.999000013f * fRec31[1]));
			fRec35[0] = ((fConst7 * fRec36[1]) + (fConst8 * fRec35[1]));
			fRec36[0] = ((float((1 - iVec0[1])) + (fConst8 * fRec36[1])) - (fConst7 * fRec35[1]));
			int iTemp20 = ((fRec35[1] <= 0.0f) & (fRec35[0] > 0.0f));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			fRec34[0] = ((fRec34[1] * float((1 - iTemp20))) + (4.65661287e-10f * (float(iRec37[0]) * float(iTemp20))));
			fRec33[0] = (fConst5 * ((fRec34[0] + fRec34[1]) - (fConst9 * fRec33[1])));
			fRec32[0] = (fRec33[0] - (fConst4 * ((fConst10 * fRec32[2]) + (fConst11 * fRec32[1]))));
			float fTemp21 = (0.5f * (fRec31[0] * ((fConst4 * (fRec32[2] + (fRec32[0] + (2.0f * fRec32[1])))) + 1.0f)));
			fRec38[0] = (fSlow8 + (0.999000013f * fRec38[1]));
			float fTemp22 = (fTemp21 + (142.0f * fRec38[0]));
			float fTemp23 = (fTemp22 + -2.99999499f);
			int iTemp24 = int(fTemp23);
			float fTemp25 = std::floor(fTemp23);
			float fTemp26 = (fTemp22 + (-2.0f - fTemp25));
			float fTemp27 = (fTemp22 + (-3.0f - fTemp25));
			float fTemp28 = (fTemp22 + (-4.0f - fTemp25));
			float fTemp29 = (fTemp22 + (-5.0f - fTemp25));
			float fTemp30 = (fTemp22 + (-6.0f - fTemp25));
			float fTemp31 = (fTemp26 * fTemp27);
			float fTemp32 = (fTemp31 * fTemp28);
			fRec21[0] = ((((((fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int(iTemp24)))))) & 2047)] * (0.0f - fTemp26)) * (0.0f - (0.5f * fTemp27))) * (0.0f - (0.333333343f * fTemp28))) * (0.0f - (0.25f * fTemp29))) * (0.0f - (0.200000003f * fTemp30))) + ((fTemp22 + (-1.0f - fTemp25)) * ((((((((fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int((iTemp24 + 1))))))) & 2047)] * (0.0f - fTemp27)) * (0.0f - (0.5f * fTemp28))) * (0.0f - (0.333333343f * fTemp29))) * (0.0f - (0.25f * fTemp30))) + (0.5f * ((((fTemp26 * fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int((iTemp24 + 2))))))) & 2047)]) * (0.0f - fTemp28)) * (0.0f - (0.5f * fTemp29))) * (0.0f - (0.333333343f * fTemp30))))) + (0.166666672f * (((fTemp31 * fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int((iTemp24 + 3))))))) & 2047)]) * (0.0f - fTemp29)) * (0.0f - (0.5f * fTemp30))))) + (0.0416666679f * ((fTemp32 * fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int((iTemp24 + 4))))))) & 2047)]) * (0.0f - fTemp30)))) + (0.00833333377f * ((fTemp32 * fTemp29) * fVec4[((IOTA - int(std::min<float>(1349.0f, float(std::max<int>(0, int((iTemp24 + 5))))))) & 2047)])))));
			float fRec22 = (0.75f * fTemp19);
			float fTemp33 = ((fRec22 + fRec21[1]) - (0.75f * fRec19[1]));
			fVec5[(IOTA & 1023)] = fTemp33;
			float fTemp34 = (fTemp21 + (107.0f * fRec38[0]));
			float fTemp35 = (fTemp34 + -2.99999499f);
			int iTemp36 = int(fTemp35);
			float fTemp37 = std::floor(fTemp35);
			float fTemp38 = (fTemp34 + (-2.0f - fTemp37));
			float fTemp39 = (fTemp34 + (-3.0f - fTemp37));
			float fTemp40 = (fTemp34 + (-4.0f - fTemp37));
			float fTemp41 = (fTemp34 + (-5.0f - fTemp37));
			float fTemp42 = (fTemp34 + (-6.0f - fTemp37));
			float fTemp43 = (fTemp38 * fTemp39);
			float fTemp44 = (fTemp43 * fTemp40);
			fRec19[0] = ((((((fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int(iTemp36)))))) & 1023)] * (0.0f - fTemp38)) * (0.0f - (0.5f * fTemp39))) * (0.0f - (0.333333343f * fTemp40))) * (0.0f - (0.25f * fTemp41))) * (0.0f - (0.200000003f * fTemp42))) + ((fTemp34 + (-1.0f - fTemp37)) * ((((((((fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int((iTemp36 + 1))))))) & 1023)] * (0.0f - fTemp39)) * (0.0f - (0.5f * fTemp40))) * (0.0f - (0.333333343f * fTemp41))) * (0.0f - (0.25f * fTemp42))) + (0.5f * ((((fTemp38 * fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int((iTemp36 + 2))))))) & 1023)]) * (0.0f - fTemp40)) * (0.0f - (0.5f * fTemp41))) * (0.0f - (0.333333343f * fTemp42))))) + (0.166666672f * (((fTemp43 * fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int((iTemp36 + 3))))))) & 1023)]) * (0.0f - fTemp41)) * (0.0f - (0.5f * fTemp42))))) + (0.0416666679f * ((fTemp44 * fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int((iTemp36 + 4))))))) & 1023)]) * (0.0f - fTemp42)))) + (0.00833333377f * ((fTemp44 * fTemp41) * fVec5[((IOTA - int(std::min<float>(1016.5f, float(std::max<int>(0, int((iTemp36 + 5))))))) & 1023)])))));
			float fRec20 = (0.75f * fTemp33);
			float fTemp45 = ((fRec20 + fRec19[1]) - (0.625f * fRec17[1]));
			fVec6[(IOTA & 4095)] = fTemp45;
			float fTemp46 = (fTemp21 + (379.0f * fRec38[0]));
			float fTemp47 = (fTemp46 + -2.99999499f);
			int iTemp48 = int(fTemp47);
			float fTemp49 = std::floor(fTemp47);
			float fTemp50 = (fTemp46 + (-2.0f - fTemp49));
			float fTemp51 = (fTemp46 + (-3.0f - fTemp49));
			float fTemp52 = (fTemp46 + (-4.0f - fTemp49));
			float fTemp53 = (fTemp46 + (-5.0f - fTemp49));
			float fTemp54 = (fTemp46 + (-6.0f - fTemp49));
			float fTemp55 = (fTemp50 * fTemp51);
			float fTemp56 = (fTemp55 * fTemp52);
			fRec17[0] = ((((((fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int(iTemp48)))))) & 4095)] * (0.0f - fTemp50)) * (0.0f - (0.5f * fTemp51))) * (0.0f - (0.333333343f * fTemp52))) * (0.0f - (0.25f * fTemp53))) * (0.0f - (0.200000003f * fTemp54))) + ((fTemp46 + (-1.0f - fTemp49)) * ((((((((fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int((iTemp48 + 1))))))) & 4095)] * (0.0f - fTemp51)) * (0.0f - (0.5f * fTemp52))) * (0.0f - (0.333333343f * fTemp53))) * (0.0f - (0.25f * fTemp54))) + (0.5f * ((((fTemp50 * fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int((iTemp48 + 2))))))) & 4095)]) * (0.0f - fTemp52)) * (0.0f - (0.5f * fTemp53))) * (0.0f - (0.333333343f * fTemp54))))) + (0.166666672f * (((fTemp55 * fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int((iTemp48 + 3))))))) & 4095)]) * (0.0f - fTemp53)) * (0.0f - (0.5f * fTemp54))))) + (0.0416666679f * ((fTemp56 * fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int((iTemp48 + 4))))))) & 4095)]) * (0.0f - fTemp54)))) + (0.00833333377f * ((fTemp56 * fTemp53) * fVec6[((IOTA - int(std::min<float>(3600.5f, float(std::max<int>(0, int((iTemp48 + 5))))))) & 4095)])))));
			float fRec18 = (0.625f * fTemp45);
			float fTemp57 = ((fRec18 + fRec17[1]) - (0.625f * fRec15[1]));
			fVec7[(IOTA & 4095)] = fTemp57;
			float fTemp58 = (fTemp21 + (277.0f * fRec38[0]));
			float fTemp59 = (fTemp58 + -2.99999499f);
			int iTemp60 = int(fTemp59);
			float fTemp61 = std::floor(fTemp59);
			float fTemp62 = (fTemp58 + (-2.0f - fTemp61));
			float fTemp63 = (fTemp58 + (-3.0f - fTemp61));
			float fTemp64 = (fTemp58 + (-4.0f - fTemp61));
			float fTemp65 = (fTemp58 + (-5.0f - fTemp61));
			float fTemp66 = (fTemp58 + (-6.0f - fTemp61));
			float fTemp67 = (fTemp62 * fTemp63);
			float fTemp68 = (fTemp67 * fTemp64);
			fRec15[0] = ((((((fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int(iTemp60)))))) & 4095)] * (0.0f - fTemp62)) * (0.0f - (0.5f * fTemp63))) * (0.0f - (0.333333343f * fTemp64))) * (0.0f - (0.25f * fTemp65))) * (0.0f - (0.200000003f * fTemp66))) + ((fTemp58 + (-1.0f - fTemp61)) * ((((((((fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int((iTemp60 + 1))))))) & 4095)] * (0.0f - fTemp63)) * (0.0f - (0.5f * fTemp64))) * (0.0f - (0.333333343f * fTemp65))) * (0.0f - (0.25f * fTemp66))) + (0.5f * ((((fTemp62 * fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int((iTemp60 + 2))))))) & 4095)]) * (0.0f - fTemp64)) * (0.0f - (0.5f * fTemp65))) * (0.0f - (0.333333343f * fTemp66))))) + (0.166666672f * (((fTemp67 * fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int((iTemp60 + 3))))))) & 4095)]) * (0.0f - fTemp65)) * (0.0f - (0.5f * fTemp66))))) + (0.0416666679f * ((fTemp68 * fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int((iTemp60 + 4))))))) & 4095)]) * (0.0f - fTemp66)))) + (0.00833333377f * ((fTemp68 * fTemp65) * fVec7[((IOTA - int(std::min<float>(2631.5f, float(std::max<int>(0, int((iTemp60 + 5))))))) & 4095)])))));
			float fRec16 = (0.625f * fTemp57);
			float fTemp69 = (fRec2[1] - (0.75f * fRec45[1]));
			fVec8[(IOTA & 2047)] = fTemp69;
			float fTemp70 = ((151.0f * fRec38[0]) + fTemp21);
			float fTemp71 = (fTemp70 + -2.99999499f);
			int iTemp72 = int(fTemp71);
			float fTemp73 = std::floor(fTemp71);
			float fTemp74 = (fTemp70 + (-2.0f - fTemp73));
			float fTemp75 = (fTemp70 + (-3.0f - fTemp73));
			float fTemp76 = (fTemp70 + (-4.0f - fTemp73));
			float fTemp77 = (fTemp70 + (-5.0f - fTemp73));
			float fTemp78 = (fTemp70 + (-6.0f - fTemp73));
			float fTemp79 = (fTemp74 * fTemp75);
			float fTemp80 = (fTemp79 * fTemp76);
			fRec45[0] = ((((((fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int(iTemp72)))))) & 2047)] * (0.0f - fTemp74)) * (0.0f - (0.5f * fTemp75))) * (0.0f - (0.333333343f * fTemp76))) * (0.0f - (0.25f * fTemp77))) * (0.0f - (0.200000003f * fTemp78))) + ((fTemp70 + (-1.0f - fTemp73)) * ((((((((fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int((iTemp72 + 1))))))) & 2047)] * (0.0f - fTemp75)) * (0.0f - (0.5f * fTemp76))) * (0.0f - (0.333333343f * fTemp77))) * (0.0f - (0.25f * fTemp78))) + (0.5f * ((((fTemp74 * fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int((iTemp72 + 2))))))) & 2047)]) * (0.0f - fTemp76)) * (0.0f - (0.5f * fTemp77))) * (0.0f - (0.333333343f * fTemp78))))) + (0.166666672f * (((fTemp79 * fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int((iTemp72 + 3))))))) & 2047)]) * (0.0f - fTemp77)) * (0.0f - (0.5f * fTemp78))))) + (0.0416666679f * ((fTemp80 * fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int((iTemp72 + 4))))))) & 2047)]) * (0.0f - fTemp78)))) + (0.00833333377f * ((fTemp80 * fTemp77) * fVec8[((IOTA - int(std::min<float>(1434.5f, float(std::max<int>(0, int((iTemp72 + 5))))))) & 2047)])))));
			float fRec46 = (0.75f * fTemp69);
			float fTemp81 = ((fRec46 + fRec45[1]) - (0.75f * fRec43[1]));
			fVec9[(IOTA & 1023)] = fTemp81;
			float fTemp82 = (fTemp21 + (101.0f * fRec38[0]));
			float fTemp83 = (fTemp82 + -2.99999499f);
			int iTemp84 = int(fTemp83);
			float fTemp85 = std::floor(fTemp83);
			float fTemp86 = (fTemp82 + (-2.0f - fTemp85));
			float fTemp87 = (fTemp82 + (-3.0f - fTemp85));
			float fTemp88 = (fTemp82 + (-4.0f - fTemp85));
			float fTemp89 = (fTemp82 + (-5.0f - fTemp85));
			float fTemp90 = (fTemp82 + (-6.0f - fTemp85));
			float fTemp91 = (fTemp86 * fTemp87);
			float fTemp92 = (fTemp91 * fTemp88);
			fRec43[0] = ((((((fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int(iTemp84)))))) & 1023)] * (0.0f - fTemp86)) * (0.0f - (0.5f * fTemp87))) * (0.0f - (0.333333343f * fTemp88))) * (0.0f - (0.25f * fTemp89))) * (0.0f - (0.200000003f * fTemp90))) + ((fTemp82 + (-1.0f - fTemp85)) * ((((((((fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int((iTemp84 + 1))))))) & 1023)] * (0.0f - fTemp87)) * (0.0f - (0.5f * fTemp88))) * (0.0f - (0.333333343f * fTemp89))) * (0.0f - (0.25f * fTemp90))) + (0.5f * ((((fTemp86 * fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int((iTemp84 + 2))))))) & 1023)]) * (0.0f - fTemp88)) * (0.0f - (0.5f * fTemp89))) * (0.0f - (0.333333343f * fTemp90))))) + (0.166666672f * (((fTemp91 * fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int((iTemp84 + 3))))))) & 1023)]) * (0.0f - fTemp89)) * (0.0f - (0.5f * fTemp90))))) + (0.0416666679f * ((fTemp92 * fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int((iTemp84 + 4))))))) & 1023)]) * (0.0f - fTemp90)))) + (0.00833333377f * ((fTemp92 * fTemp89) * fVec9[((IOTA - int(std::min<float>(959.5f, float(std::max<int>(0, int((iTemp84 + 5))))))) & 1023)])))));
			float fRec44 = (0.75f * fTemp81);
			float fTemp93 = ((fRec44 + fRec43[1]) - (0.625f * fRec41[1]));
			fVec10[(IOTA & 4095)] = fTemp93;
			float fTemp94 = (fTemp21 + (367.0f * fRec38[0]));
			float fTemp95 = (fTemp94 + -2.99999499f);
			int iTemp96 = int(fTemp95);
			float fTemp97 = std::floor(fTemp95);
			float fTemp98 = (fTemp94 + (-2.0f - fTemp97));
			float fTemp99 = (fTemp94 + (-3.0f - fTemp97));
			float fTemp100 = (fTemp94 + (-4.0f - fTemp97));
			float fTemp101 = (fTemp94 + (-5.0f - fTemp97));
			float fTemp102 = (fTemp94 + (-6.0f - fTemp97));
			float fTemp103 = (fTemp98 * fTemp99);
			float fTemp104 = (fTemp103 * fTemp100);
			fRec41[0] = ((((((fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int(iTemp96)))))) & 4095)] * (0.0f - fTemp98)) * (0.0f - (0.5f * fTemp99))) * (0.0f - (0.333333343f * fTemp100))) * (0.0f - (0.25f * fTemp101))) * (0.0f - (0.200000003f * fTemp102))) + ((fTemp94 + (-1.0f - fTemp97)) * ((((((((fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int((iTemp96 + 1))))))) & 4095)] * (0.0f - fTemp99)) * (0.0f - (0.5f * fTemp100))) * (0.0f - (0.333333343f * fTemp101))) * (0.0f - (0.25f * fTemp102))) + (0.5f * ((((fTemp98 * fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int((iTemp96 + 2))))))) & 4095)]) * (0.0f - fTemp100)) * (0.0f - (0.5f * fTemp101))) * (0.0f - (0.333333343f * fTemp102))))) + (0.166666672f * (((fTemp103 * fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int((iTemp96 + 3))))))) & 4095)]) * (0.0f - fTemp101)) * (0.0f - (0.5f * fTemp102))))) + (0.0416666679f * ((fTemp104 * fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int((iTemp96 + 4))))))) & 4095)]) * (0.0f - fTemp102)))) + (0.00833333377f * ((fTemp104 * fTemp101) * fVec10[((IOTA - int(std::min<float>(3486.5f, float(std::max<int>(0, int((iTemp96 + 5))))))) & 4095)])))));
			float fRec42 = (0.625f * fTemp93);
			float fTemp105 = ((fRec42 + fRec41[1]) - (0.625f * fRec39[1]));
			fVec11[(IOTA & 4095)] = fTemp105;
			float fTemp106 = (fTemp21 + (281.0f * fRec38[0]));
			float fTemp107 = (fTemp106 + -2.99999499f);
			int iTemp108 = int(fTemp107);
			float fTemp109 = std::floor(fTemp107);
			float fTemp110 = (fTemp106 + (-2.0f - fTemp109));
			float fTemp111 = (fTemp106 + (-3.0f - fTemp109));
			float fTemp112 = (fTemp106 + (-4.0f - fTemp109));
			float fTemp113 = (fTemp106 + (-5.0f - fTemp109));
			float fTemp114 = (fTemp106 + (-6.0f - fTemp109));
			float fTemp115 = (fTemp110 * fTemp111);
			float fTemp116 = (fTemp115 * fTemp112);
			fRec39[0] = ((((((fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int(iTemp108)))))) & 4095)] * (0.0f - fTemp110)) * (0.0f - (0.5f * fTemp111))) * (0.0f - (0.333333343f * fTemp112))) * (0.0f - (0.25f * fTemp113))) * (0.0f - (0.200000003f * fTemp114))) + ((fTemp106 + (-1.0f - fTemp109)) * ((((((((fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int((iTemp108 + 1))))))) & 4095)] * (0.0f - fTemp111)) * (0.0f - (0.5f * fTemp112))) * (0.0f - (0.333333343f * fTemp113))) * (0.0f - (0.25f * fTemp114))) + (0.5f * ((((fTemp110 * fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int((iTemp108 + 2))))))) & 4095)]) * (0.0f - fTemp112)) * (0.0f - (0.5f * fTemp113))) * (0.0f - (0.333333343f * fTemp114))))) + (0.166666672f * (((fTemp115 * fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int((iTemp108 + 3))))))) & 4095)]) * (0.0f - fTemp113)) * (0.0f - (0.5f * fTemp114))))) + (0.0416666679f * ((fTemp116 * fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int((iTemp108 + 4))))))) & 4095)]) * (0.0f - fTemp114)))) + (0.00833333377f * ((fTemp116 * fTemp113) * fVec11[((IOTA - int(std::min<float>(2669.5f, float(std::max<int>(0, int((iTemp108 + 5))))))) & 4095)])))));
			float fRec40 = (0.625f * fTemp105);
			float fTemp117 = (fRec15[1] + (fRec16 + (fSlow1 * (fRec40 + fRec39[1]))));
			float fTemp118 = std::fabs(fTemp117);
			float fTemp119 = ((fRec48[1] > fTemp118) ? fConst15 : fConst14);
			fRec49[0] = ((fRec49[1] * fTemp119) + (fTemp118 * (1.0f - fTemp119)));
			fRec48[0] = fRec49[0];
			fRec47[0] = ((fConst12 * fRec47[1]) + (fConst13 * (0.0f - (0.800000012f * std::max<float>(((20.0f * std::log10(fRec48[0])) + 6.0f), 0.0f)))));
			float fTemp120 = ((0.699999988f * fRec13[1]) + (fTemp117 * std::pow(10.0f, (0.0500000007f * fRec47[0]))));
			fVec12[(IOTA & 4095)] = fTemp120;
			fRec50[0] = (fSlow9 + (0.999000013f * fRec50[1]));
			float fTemp121 = (fTemp21 + (672.0f * fRec50[0]));
			float fTemp122 = (fTemp121 + -2.99999499f);
			int iTemp123 = int(fTemp122);
			float fTemp124 = std::floor(fTemp122);
			float fTemp125 = (fTemp121 + (-2.0f - fTemp124));
			float fTemp126 = (fTemp121 + (-3.0f - fTemp124));
			float fTemp127 = (fTemp121 + (-4.0f - fTemp124));
			float fTemp128 = (fTemp121 + (-5.0f - fTemp124));
			float fTemp129 = (fTemp121 + (-6.0f - fTemp124));
			float fTemp130 = (fTemp125 * fTemp126);
			float fTemp131 = (fTemp130 * fTemp127);
			fRec13[0] = ((((((fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int(iTemp123))))) & 4095)] * (0.0f - fTemp125)) * (0.0f - (0.5f * fTemp126))) * (0.0f - (0.333333343f * fTemp127))) * (0.0f - (0.25f * fTemp128))) * (0.0f - (0.200000003f * fTemp129))) + ((fTemp121 + (-1.0f - fTemp124)) * ((((((((fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int((iTemp123 + 1)))))) & 4095)] * (0.0f - fTemp126)) * (0.0f - (0.5f * fTemp127))) * (0.0f - (0.333333343f * fTemp128))) * (0.0f - (0.25f * fTemp129))) + (0.5f * ((((fTemp125 * fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int((iTemp123 + 2)))))) & 4095)]) * (0.0f - fTemp127)) * (0.0f - (0.5f * fTemp128))) * (0.0f - (0.333333343f * fTemp129))))) + (0.166666672f * (((fTemp130 * fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int((iTemp123 + 3)))))) & 4095)]) * (0.0f - fTemp128)) * (0.0f - (0.5f * fTemp129))))) + (0.0416666679f * ((fTemp131 * fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int((iTemp123 + 4)))))) & 4095)]) * (0.0f - fTemp129)))) + (0.00833333377f * ((fTemp131 * fTemp128) * fVec12[((IOTA - std::min<int>(3510, int(std::max<int>(0, int((iTemp123 + 5)))))) & 4095)])))));
			float fRec14 = (0.0f - (0.699999988f * fTemp120));
			float fTemp132 = (fRec14 + fRec13[1]);
			fVec13[(IOTA & 8191)] = fTemp132;
			fRec11[0] = ((fRec12[0] * fRec11[2]) + (fTemp0 * (((6.31716901e-14f * fVec13[((IOTA - 4452) & 8191)]) + (1.0f * fVec13[((IOTA - 4453) & 8191)])) - (6.31716918e-15f * fVec13[((IOTA - 4451) & 8191)]))));
			float fTemp133 = ((fSlow1 * fRec11[0]) - (0.5f * fRec7[1]));
			fVec14[(IOTA & 16383)] = fTemp133;
			float fTemp134 = (fTemp21 + (1800.0f * fRec50[0]));
			float fTemp135 = (fTemp134 + -2.99999499f);
			int iTemp136 = int(fTemp135);
			float fTemp137 = std::floor(fTemp135);
			float fTemp138 = (fTemp134 + (-2.0f - fTemp137));
			float fTemp139 = (fTemp134 + (-3.0f - fTemp137));
			float fTemp140 = (fTemp134 + (-4.0f - fTemp137));
			float fTemp141 = (fTemp134 + (-5.0f - fTemp137));
			float fTemp142 = (fTemp134 + (-6.0f - fTemp137));
			float fTemp143 = (fTemp138 * fTemp139);
			float fTemp144 = (fTemp143 * fTemp140);
			fRec7[0] = ((((((fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int(iTemp136))))) & 16383)] * (0.0f - fTemp138)) * (0.0f - (0.5f * fTemp139))) * (0.0f - (0.333333343f * fTemp140))) * (0.0f - (0.25f * fTemp141))) * (0.0f - (0.200000003f * fTemp142))) + ((fTemp134 + (-1.0f - fTemp137)) * ((((((((fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int((iTemp136 + 1)))))) & 16383)] * (0.0f - fTemp139)) * (0.0f - (0.5f * fTemp140))) * (0.0f - (0.333333343f * fTemp141))) * (0.0f - (0.25f * fTemp142))) + (0.5f * ((((fTemp138 * fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int((iTemp136 + 2)))))) & 16383)]) * (0.0f - fTemp140)) * (0.0f - (0.5f * fTemp141))) * (0.0f - (0.333333343f * fTemp142))))) + (0.166666672f * (((fTemp143 * fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int((iTemp136 + 3)))))) & 16383)]) * (0.0f - fTemp141)) * (0.0f - (0.5f * fTemp142))))) + (0.0416666679f * ((fTemp144 * fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int((iTemp136 + 4)))))) & 16383)]) * (0.0f - fTemp142)))) + (0.00833333377f * ((fTemp144 * fTemp141) * fVec14[((IOTA - std::min<int>(9150, int(std::max<int>(0, int((iTemp136 + 5)))))) & 16383)])))));
			float fRec8 = (0.5f * fTemp133);
			float fTemp145 = (186.915894f * fRec50[0]);
			float fTemp146 = (fTemp145 + -1.99999499f);
			int iTemp147 = int(fTemp146);
			float fTemp148 = std::floor(fTemp146);
			float fTemp149 = (fTemp145 + (-1.0f - fTemp148));
			float fTemp150 = (fTemp145 + (-2.0f - fTemp148));
			float fTemp151 = (fTemp145 + (-3.0f - fTemp148));
			float fTemp152 = (fTemp145 + (-4.0f - fTemp148));
			float fTemp153 = (fTemp145 + (-5.0f - fTemp148));
			float fTemp154 = (fTemp149 * fTemp150);
			float fTemp155 = (fTemp154 * fTemp151);
			float fRec9 = ((((((fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, iTemp147))) & 16383)] * (0.0f - fTemp149)) * (0.0f - (0.5f * fTemp150))) * (0.0f - (0.333333343f * fTemp151))) * (0.0f - (0.25f * fTemp152))) * (0.0f - (0.200000003f * fTemp153))) + ((fTemp145 - fTemp148) * ((((((((fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp147 + 1)))) & 16383)] * (0.0f - fTemp150)) * (0.0f - (0.5f * fTemp151))) * (0.0f - (0.333333343f * fTemp152))) * (0.0f - (0.25f * fTemp153))) + (0.5f * ((((fTemp149 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp147 + 2)))) & 16383)]) * (0.0f - fTemp151)) * (0.0f - (0.5f * fTemp152))) * (0.0f - (0.333333343f * fTemp153))))) + (0.166666672f * (((fTemp154 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp147 + 3)))) & 16383)]) * (0.0f - fTemp152)) * (0.0f - (0.5f * fTemp153))))) + (0.0416666679f * ((fTemp155 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp147 + 4)))) & 16383)]) * (0.0f - fTemp153)))) + (0.00833333377f * ((fTemp155 * fTemp152) * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp147 + 5)))) & 16383)])))));
			float fTemp156 = (1232.87671f * fRec50[0]);
			float fTemp157 = (fTemp156 + -1.99999499f);
			int iTemp158 = int(fTemp157);
			float fTemp159 = std::floor(fTemp157);
			float fTemp160 = (fTemp156 + (-1.0f - fTemp159));
			float fTemp161 = (fTemp156 + (-2.0f - fTemp159));
			float fTemp162 = (fTemp156 + (-3.0f - fTemp159));
			float fTemp163 = (fTemp156 + (-4.0f - fTemp159));
			float fTemp164 = (fTemp156 + (-5.0f - fTemp159));
			float fTemp165 = (fTemp160 * fTemp161);
			float fTemp166 = (fTemp165 * fTemp162);
			float fRec10 = ((((((fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, iTemp158))) & 16383)] * (0.0f - fTemp160)) * (0.0f - (0.5f * fTemp161))) * (0.0f - (0.333333343f * fTemp162))) * (0.0f - (0.25f * fTemp163))) * (0.0f - (0.200000003f * fTemp164))) + ((fTemp156 - fTemp159) * ((((((((fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp158 + 1)))) & 16383)] * (0.0f - fTemp161)) * (0.0f - (0.5f * fTemp162))) * (0.0f - (0.333333343f * fTemp163))) * (0.0f - (0.25f * fTemp164))) + (0.5f * ((((fTemp160 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp158 + 2)))) & 16383)]) * (0.0f - fTemp162)) * (0.0f - (0.5f * fTemp163))) * (0.0f - (0.333333343f * fTemp164))))) + (0.166666672f * (((fTemp165 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp158 + 3)))) & 16383)]) * (0.0f - fTemp163)) * (0.0f - (0.5f * fTemp164))))) + (0.0416666679f * ((fTemp166 * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp158 + 4)))) & 16383)]) * (0.0f - fTemp164)))) + (0.00833333377f * ((fTemp166 * fTemp163) * fVec14[((IOTA - std::min<int>(9150, std::max<int>(0, (iTemp158 + 5)))) & 16383)])))));
			float fTemp167 = (fRec8 + fRec7[1]);
			fVec15[(IOTA & 4095)] = fTemp167;
			fRec1[0] = (fSlow1 * fVec15[((IOTA - 3720) & 4095)]);
			float fTemp168 = (fRec1[1] - (0.75f * fRec64[1]));
			fVec16[(IOTA & 2047)] = fTemp168;
			float fTemp169 = (fTemp21 + (149.0f * fRec38[0]));
			float fTemp170 = (fTemp169 + -2.99999499f);
			int iTemp171 = int(fTemp170);
			float fTemp172 = std::floor(fTemp170);
			float fTemp173 = (fTemp169 + (-2.0f - fTemp172));
			float fTemp174 = (fTemp169 + (-3.0f - fTemp172));
			float fTemp175 = (fTemp169 + (-4.0f - fTemp172));
			float fTemp176 = (fTemp169 + (-5.0f - fTemp172));
			float fTemp177 = (fTemp169 + (-6.0f - fTemp172));
			float fTemp178 = (fTemp173 * fTemp174);
			float fTemp179 = (fTemp178 * fTemp175);
			fRec64[0] = ((((((fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int(iTemp171)))))) & 2047)] * (0.0f - fTemp173)) * (0.0f - (0.5f * fTemp174))) * (0.0f - (0.333333343f * fTemp175))) * (0.0f - (0.25f * fTemp176))) * (0.0f - (0.200000003f * fTemp177))) + ((fTemp169 + (-1.0f - fTemp172)) * ((((((((fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int((iTemp171 + 1))))))) & 2047)] * (0.0f - fTemp174)) * (0.0f - (0.5f * fTemp175))) * (0.0f - (0.333333343f * fTemp176))) * (0.0f - (0.25f * fTemp177))) + (0.5f * ((((fTemp173 * fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int((iTemp171 + 2))))))) & 2047)]) * (0.0f - fTemp175)) * (0.0f - (0.5f * fTemp176))) * (0.0f - (0.333333343f * fTemp177))))) + (0.166666672f * (((fTemp178 * fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int((iTemp171 + 3))))))) & 2047)]) * (0.0f - fTemp176)) * (0.0f - (0.5f * fTemp177))))) + (0.0416666679f * ((fTemp179 * fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int((iTemp171 + 4))))))) & 2047)]) * (0.0f - fTemp177)))) + (0.00833333377f * ((fTemp179 * fTemp176) * fVec16[((IOTA - int(std::min<float>(1415.5f, float(std::max<int>(0, int((iTemp171 + 5))))))) & 2047)])))));
			float fRec65 = (0.75f * fTemp168);
			float fTemp180 = ((fRec65 + fRec64[1]) - (0.75f * fRec62[1]));
			fVec17[(IOTA & 2047)] = fTemp180;
			float fTemp181 = (fTemp21 + (113.0f * fRec38[0]));
			float fTemp182 = (fTemp181 + -2.99999499f);
			int iTemp183 = int(fTemp182);
			float fTemp184 = std::floor(fTemp182);
			float fTemp185 = (fTemp181 + (-2.0f - fTemp184));
			float fTemp186 = (fTemp181 + (-3.0f - fTemp184));
			float fTemp187 = (fTemp181 + (-4.0f - fTemp184));
			float fTemp188 = (fTemp181 + (-5.0f - fTemp184));
			float fTemp189 = (fTemp181 + (-6.0f - fTemp184));
			float fTemp190 = (fTemp185 * fTemp186);
			float fTemp191 = (fTemp190 * fTemp187);
			fRec62[0] = ((((((fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int(iTemp183)))))) & 2047)] * (0.0f - fTemp185)) * (0.0f - (0.5f * fTemp186))) * (0.0f - (0.333333343f * fTemp187))) * (0.0f - (0.25f * fTemp188))) * (0.0f - (0.200000003f * fTemp189))) + ((fTemp181 + (-1.0f - fTemp184)) * ((((((((fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int((iTemp183 + 1))))))) & 2047)] * (0.0f - fTemp186)) * (0.0f - (0.5f * fTemp187))) * (0.0f - (0.333333343f * fTemp188))) * (0.0f - (0.25f * fTemp189))) + (0.5f * ((((fTemp185 * fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int((iTemp183 + 2))))))) & 2047)]) * (0.0f - fTemp187)) * (0.0f - (0.5f * fTemp188))) * (0.0f - (0.333333343f * fTemp189))))) + (0.166666672f * (((fTemp190 * fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int((iTemp183 + 3))))))) & 2047)]) * (0.0f - fTemp188)) * (0.0f - (0.5f * fTemp189))))) + (0.0416666679f * ((fTemp191 * fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int((iTemp183 + 4))))))) & 2047)]) * (0.0f - fTemp189)))) + (0.00833333377f * ((fTemp191 * fTemp188) * fVec17[((IOTA - int(std::min<float>(1073.5f, float(std::max<int>(0, int((iTemp183 + 5))))))) & 2047)])))));
			float fRec63 = (0.75f * fTemp180);
			float fTemp192 = ((fRec63 + fRec62[1]) - (0.625f * fRec60[1]));
			fVec18[(IOTA & 4095)] = fTemp192;
			float fTemp193 = (fTemp21 + (397.0f * fRec38[0]));
			float fTemp194 = (fTemp193 + -2.99999499f);
			int iTemp195 = int(fTemp194);
			float fTemp196 = std::floor(fTemp194);
			float fTemp197 = (fTemp193 + (-2.0f - fTemp196));
			float fTemp198 = (fTemp193 + (-3.0f - fTemp196));
			float fTemp199 = (fTemp193 + (-4.0f - fTemp196));
			float fTemp200 = (fTemp193 + (-5.0f - fTemp196));
			float fTemp201 = (fTemp193 + (-6.0f - fTemp196));
			float fTemp202 = (fTemp197 * fTemp198);
			float fTemp203 = (fTemp202 * fTemp199);
			fRec60[0] = ((((((fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int(iTemp195)))))) & 4095)] * (0.0f - fTemp197)) * (0.0f - (0.5f * fTemp198))) * (0.0f - (0.333333343f * fTemp199))) * (0.0f - (0.25f * fTemp200))) * (0.0f - (0.200000003f * fTemp201))) + ((fTemp193 + (-1.0f - fTemp196)) * ((((((((fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int((iTemp195 + 1))))))) & 4095)] * (0.0f - fTemp198)) * (0.0f - (0.5f * fTemp199))) * (0.0f - (0.333333343f * fTemp200))) * (0.0f - (0.25f * fTemp201))) + (0.5f * ((((fTemp197 * fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int((iTemp195 + 2))))))) & 4095)]) * (0.0f - fTemp199)) * (0.0f - (0.5f * fTemp200))) * (0.0f - (0.333333343f * fTemp201))))) + (0.166666672f * (((fTemp202 * fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int((iTemp195 + 3))))))) & 4095)]) * (0.0f - fTemp200)) * (0.0f - (0.5f * fTemp201))))) + (0.0416666679f * ((fTemp203 * fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int((iTemp195 + 4))))))) & 4095)]) * (0.0f - fTemp201)))) + (0.00833333377f * ((fTemp203 * fTemp200) * fVec18[((IOTA - int(std::min<float>(3771.5f, float(std::max<int>(0, int((iTemp195 + 5))))))) & 4095)])))));
			float fRec61 = (0.625f * fTemp192);
			float fTemp204 = ((fRec61 + fRec60[1]) - (0.625f * fRec58[1]));
			fVec19[(IOTA & 4095)] = fTemp204;
			float fTemp205 = (fTemp21 + (283.0f * fRec38[0]));
			float fTemp206 = (fTemp205 + -2.99999499f);
			int iTemp207 = int(fTemp206);
			float fTemp208 = std::floor(fTemp206);
			float fTemp209 = (fTemp205 + (-2.0f - fTemp208));
			float fTemp210 = (fTemp205 + (-3.0f - fTemp208));
			float fTemp211 = (fTemp205 + (-4.0f - fTemp208));
			float fTemp212 = (fTemp205 + (-5.0f - fTemp208));
			float fTemp213 = (fTemp205 + (-6.0f - fTemp208));
			float fTemp214 = (fTemp209 * fTemp210);
			float fTemp215 = (fTemp214 * fTemp211);
			fRec58[0] = ((((((fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int(iTemp207)))))) & 4095)] * (0.0f - fTemp209)) * (0.0f - (0.5f * fTemp210))) * (0.0f - (0.333333343f * fTemp211))) * (0.0f - (0.25f * fTemp212))) * (0.0f - (0.200000003f * fTemp213))) + ((fTemp205 + (-1.0f - fTemp208)) * ((((((((fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int((iTemp207 + 1))))))) & 4095)] * (0.0f - fTemp210)) * (0.0f - (0.5f * fTemp211))) * (0.0f - (0.333333343f * fTemp212))) * (0.0f - (0.25f * fTemp213))) + (0.5f * ((((fTemp209 * fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int((iTemp207 + 2))))))) & 4095)]) * (0.0f - fTemp211)) * (0.0f - (0.5f * fTemp212))) * (0.0f - (0.333333343f * fTemp213))))) + (0.166666672f * (((fTemp214 * fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int((iTemp207 + 3))))))) & 4095)]) * (0.0f - fTemp212)) * (0.0f - (0.5f * fTemp213))))) + (0.0416666679f * ((fTemp215 * fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int((iTemp207 + 4))))))) & 4095)]) * (0.0f - fTemp213)))) + (0.00833333377f * ((fTemp215 * fTemp212) * fVec19[((IOTA - int(std::min<float>(2688.5f, float(std::max<int>(0, int((iTemp207 + 5))))))) & 4095)])))));
			float fRec59 = (0.625f * fTemp204);
			float fTemp216 = (fRec15[1] + (fRec16 + (fSlow1 * (fRec59 + fRec58[1]))));
			float fTemp217 = std::fabs(fTemp216);
			float fTemp218 = ((fRec67[1] > fTemp217) ? fConst15 : fConst14);
			fRec68[0] = ((fRec68[1] * fTemp218) + (fTemp217 * (1.0f - fTemp218)));
			fRec67[0] = fRec68[0];
			fRec66[0] = ((fConst12 * fRec66[1]) + (fConst13 * (0.0f - (0.800000012f * std::max<float>(((20.0f * std::log10(fRec67[0])) + 6.0f), 0.0f)))));
			float fTemp219 = ((0.699999988f * fRec56[1]) + (fTemp216 * std::pow(10.0f, (0.0500000007f * fRec66[0]))));
			fVec20[(IOTA & 8191)] = fTemp219;
			float fTemp220 = (fTemp21 + (908.0f * fRec50[0]));
			float fTemp221 = (fTemp220 + -2.99999499f);
			int iTemp222 = int(fTemp221);
			float fTemp223 = std::floor(fTemp221);
			float fTemp224 = (fTemp220 + (-2.0f - fTemp223));
			float fTemp225 = (fTemp220 + (-3.0f - fTemp223));
			float fTemp226 = (fTemp220 + (-4.0f - fTemp223));
			float fTemp227 = (fTemp220 + (-5.0f - fTemp223));
			float fTemp228 = (fTemp220 + (-6.0f - fTemp223));
			float fTemp229 = (fTemp224 * fTemp225);
			float fTemp230 = (fTemp229 * fTemp226);
			fRec56[0] = ((((((fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int(iTemp222))))) & 8191)] * (0.0f - fTemp224)) * (0.0f - (0.5f * fTemp225))) * (0.0f - (0.333333343f * fTemp226))) * (0.0f - (0.25f * fTemp227))) * (0.0f - (0.200000003f * fTemp228))) + ((fTemp220 + (-1.0f - fTemp223)) * ((((((((fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int((iTemp222 + 1)))))) & 8191)] * (0.0f - fTemp225)) * (0.0f - (0.5f * fTemp226))) * (0.0f - (0.333333343f * fTemp227))) * (0.0f - (0.25f * fTemp228))) + (0.5f * ((((fTemp224 * fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int((iTemp222 + 2)))))) & 8191)]) * (0.0f - fTemp226)) * (0.0f - (0.5f * fTemp227))) * (0.0f - (0.333333343f * fTemp228))))) + (0.166666672f * (((fTemp229 * fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int((iTemp222 + 3)))))) & 8191)]) * (0.0f - fTemp227)) * (0.0f - (0.5f * fTemp228))))) + (0.0416666679f * ((fTemp230 * fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int((iTemp222 + 4)))))) & 8191)]) * (0.0f - fTemp228)))) + (0.00833333377f * ((fTemp230 * fTemp227) * fVec20[((IOTA - std::min<int>(4690, int(std::max<int>(0, int((iTemp222 + 5)))))) & 8191)])))));
			float fRec57 = (0.0f - (0.699999988f * fTemp219));
			float fTemp231 = (fRec57 + fRec56[1]);
			fVec21[(IOTA & 8191)] = fTemp231;
			fRec55[0] = ((fRec12[0] * fRec55[2]) + (fTemp0 * fVec21[((IOTA - 4217) & 8191)]));
			float fTemp232 = ((fSlow1 * fRec55[0]) - (0.5f * fRec51[1]));
			fVec22[(IOTA & 16383)] = fTemp232;
			float fTemp233 = (fTemp21 + (2656.0f * fRec50[0]));
			float fTemp234 = (fTemp233 + -2.99999499f);
			int iTemp235 = int(fTemp234);
			float fTemp236 = std::floor(fTemp234);
			float fTemp237 = (fTemp233 + (-2.0f - fTemp236));
			float fTemp238 = (fTemp233 + (-3.0f - fTemp236));
			float fTemp239 = (fTemp233 + (-4.0f - fTemp236));
			float fTemp240 = (fTemp233 + (-5.0f - fTemp236));
			float fTemp241 = (fTemp233 + (-6.0f - fTemp236));
			float fTemp242 = (fTemp237 * fTemp238);
			float fTemp243 = (fTemp242 * fTemp239);
			fRec51[0] = ((((((fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int(iTemp235))))) & 16383)] * (0.0f - fTemp237)) * (0.0f - (0.5f * fTemp238))) * (0.0f - (0.333333343f * fTemp239))) * (0.0f - (0.25f * fTemp240))) * (0.0f - (0.200000003f * fTemp241))) + ((fTemp233 + (-1.0f - fTemp236)) * ((((((((fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int((iTemp235 + 1)))))) & 16383)] * (0.0f - fTemp238)) * (0.0f - (0.5f * fTemp239))) * (0.0f - (0.333333343f * fTemp240))) * (0.0f - (0.25f * fTemp241))) + (0.5f * ((((fTemp237 * fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int((iTemp235 + 2)))))) & 16383)]) * (0.0f - fTemp239)) * (0.0f - (0.5f * fTemp240))) * (0.0f - (0.333333343f * fTemp241))))) + (0.166666672f * (((fTemp242 * fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int((iTemp235 + 3)))))) & 16383)]) * (0.0f - fTemp240)) * (0.0f - (0.5f * fTemp241))))) + (0.0416666679f * ((fTemp243 * fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int((iTemp235 + 4)))))) & 16383)]) * (0.0f - fTemp241)))) + (0.00833333377f * ((fTemp243 * fTemp240) * fVec22[((IOTA - std::min<int>(13430, int(std::max<int>(0, int((iTemp235 + 5)))))) & 16383)])))));
			float fRec52 = (0.5f * fTemp232);
			float fTemp244 = (334.930634f * fRec50[0]);
			float fTemp245 = (fTemp244 + -1.99999499f);
			int iTemp246 = int(fTemp245);
			float fTemp247 = std::floor(fTemp245);
			float fTemp248 = (fTemp244 + (-1.0f - fTemp247));
			float fTemp249 = (fTemp244 + (-2.0f - fTemp247));
			float fTemp250 = (fTemp244 + (-3.0f - fTemp247));
			float fTemp251 = (fTemp244 + (-4.0f - fTemp247));
			float fTemp252 = (fTemp244 + (-5.0f - fTemp247));
			float fTemp253 = (fTemp248 * fTemp249);
			float fTemp254 = (fTemp253 * fTemp250);
			float fRec53 = ((((((fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, iTemp246))) & 16383)] * (0.0f - fTemp248)) * (0.0f - (0.5f * fTemp249))) * (0.0f - (0.333333343f * fTemp250))) * (0.0f - (0.25f * fTemp251))) * (0.0f - (0.200000003f * fTemp252))) + ((fTemp244 - fTemp247) * ((((((((fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp246 + 1)))) & 16383)] * (0.0f - fTemp249)) * (0.0f - (0.5f * fTemp250))) * (0.0f - (0.333333343f * fTemp251))) * (0.0f - (0.25f * fTemp252))) + (0.5f * ((((fTemp248 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp246 + 2)))) & 16383)]) * (0.0f - fTemp250)) * (0.0f - (0.5f * fTemp251))) * (0.0f - (0.333333343f * fTemp252))))) + (0.166666672f * (((fTemp253 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp246 + 3)))) & 16383)]) * (0.0f - fTemp251)) * (0.0f - (0.5f * fTemp252))))) + (0.0416666679f * ((fTemp254 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp246 + 4)))) & 16383)]) * (0.0f - fTemp252)))) + (0.00833333377f * ((fTemp254 * fTemp251) * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp246 + 5)))) & 16383)])))));
			float fTemp255 = (1910.79138f * fRec50[0]);
			float fTemp256 = (fTemp255 + -1.99999499f);
			int iTemp257 = int(fTemp256);
			float fTemp258 = std::floor(fTemp256);
			float fTemp259 = (fTemp255 + (-1.0f - fTemp258));
			float fTemp260 = (fTemp255 + (-2.0f - fTemp258));
			float fTemp261 = (fTemp255 + (-3.0f - fTemp258));
			float fTemp262 = (fTemp255 + (-4.0f - fTemp258));
			float fTemp263 = (fTemp255 + (-5.0f - fTemp258));
			float fTemp264 = (fTemp259 * fTemp260);
			float fTemp265 = (fTemp264 * fTemp261);
			float fRec54 = ((((((fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, iTemp257))) & 16383)] * (0.0f - fTemp259)) * (0.0f - (0.5f * fTemp260))) * (0.0f - (0.333333343f * fTemp261))) * (0.0f - (0.25f * fTemp262))) * (0.0f - (0.200000003f * fTemp263))) + ((fTemp255 - fTemp258) * ((((((((fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp257 + 1)))) & 16383)] * (0.0f - fTemp260)) * (0.0f - (0.5f * fTemp261))) * (0.0f - (0.333333343f * fTemp262))) * (0.0f - (0.25f * fTemp263))) + (0.5f * ((((fTemp259 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp257 + 2)))) & 16383)]) * (0.0f - fTemp261)) * (0.0f - (0.5f * fTemp262))) * (0.0f - (0.333333343f * fTemp263))))) + (0.166666672f * (((fTemp264 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp257 + 3)))) & 16383)]) * (0.0f - fTemp262)) * (0.0f - (0.5f * fTemp263))))) + (0.0416666679f * ((fTemp265 * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp257 + 4)))) & 16383)]) * (0.0f - fTemp263)))) + (0.00833333377f * ((fTemp265 * fTemp262) * fVec22[((IOTA - std::min<int>(13430, std::max<int>(0, (iTemp257 + 5)))) & 16383)])))));
			float fTemp266 = (fRec52 + fRec51[1]);
			fVec23[(IOTA & 4095)] = fTemp266;
			fRec2[0] = (fSlow1 * fVec23[((IOTA - 3163) & 4095)]);
			float fRec3 = (0.600000024f * (0.0f - ((0.902578771f * fVec15[((IOTA - 1066) & 4095)]) + (((0.860986531f * fVec13[((IOTA - 1997) & 8191)]) + (fRec9 + (0.139013454f * fVec13[((IOTA - 1996) & 8191)]))) + (0.0974212065f * fVec15[((IOTA - 1065) & 4095)])))));
			float fTemp267 = (353.132446f * fRec50[0]);
			int iTemp268 = int(fTemp267);
			float fTemp269 = std::floor(fTemp267);
			float fRec4 = (0.600000024f * (((0.258992791f * fVec15[((IOTA - 2677) & 4095)]) + (((0.32520324f * fVec13[((IOTA - 3621) & 8191)]) + (((fVec13[((IOTA - std::min<int>(4454, std::max<int>(0, iTemp268))) & 8191)] * (fTemp269 + (1.0f - fTemp267))) + ((fTemp267 - fTemp269) * fVec13[((IOTA - std::min<int>(4454, std::max<int>(0, (iTemp268 + 1)))) & 8191)])) + (0.67479676f * fVec13[((IOTA - 3620) & 8191)]))) + (0.741007209f * fVec15[((IOTA - 2676) & 4095)]))) - fRec10));
			float fTemp270 = (266.056793f * fRec50[0]);
			int iTemp271 = int(fTemp270);
			float fTemp272 = std::floor(fTemp270);
			float fTemp273 = (121.002296f * fRec50[0]);
			float fTemp274 = std::floor(fTemp273);
			int iTemp275 = int(fTemp273);
			float fRec5 = (0.600000024f * (((0.718309879f * fVec21[((IOTA - 2970) & 8191)]) + (((fVec21[((IOTA - std::min<int>(4218, std::max<int>(0, iTemp271))) & 8191)] * (fTemp272 + (1.0f - fTemp270))) + ((fTemp270 - fTemp272) * fVec21[((IOTA - std::min<int>(4218, std::max<int>(0, (iTemp271 + 1)))) & 8191)])) + (0.28169015f * fVec21[((IOTA - 2969) & 8191)]))) - (((fTemp273 - fTemp274) * fVec23[((IOTA - std::min<int>(3164, std::max<int>(0, (iTemp275 + 1)))) & 4095)]) + (fRec54 + (fVec23[((IOTA - std::min<int>(3164, std::max<int>(0, iTemp275))) & 4095)] * (fTemp274 + (1.0f - fTemp273)))))));
			float fRec6 = (0.600000024f * (((0.101265825f * fVec23[((IOTA - 2001) & 4095)]) + (0.898734152f * fVec23[((IOTA - 2002) & 4095)])) - (fRec53 + (0.5f * (fVec21[((IOTA - 2108) & 8191)] + fVec21[((IOTA - 2109) & 8191)])))));
			float fTemp276 = (1.0f - fRec0[0]);
			float fTemp277 = ((fRec0[0] * (fRec3 + fRec5)) + ((fTemp276 * fTemp2) * fTemp3));
			float fTemp278 = ((fRec0[0] * (fRec4 + fRec6)) + ((fTemp276 * fTemp4) * fTemp5));
			float fTemp279 = std::fabs((std::fabs(fTemp277) + std::fabs(fTemp278)));
			float fTemp280 = ((fRec70[1] > fTemp279) ? fConst14 : fConst18);
			fRec71[0] = ((fRec71[1] * fTemp280) + (fTemp279 * (1.0f - fTemp280)));
			fRec70[0] = fRec71[0];
			fRec69[0] = ((fConst16 * fRec69[1]) + (fConst17 * (0.0f - (0.75f * std::max<float>(((20.0f * std::log10(fRec70[0])) + 6.0f), 0.0f)))));
			float fTemp281 = std::pow(10.0f, (0.0500000007f * fRec69[0]));
			output0[i] = FAUSTFLOAT((fTemp277 * fTemp281));
			output1[i] = FAUSTFLOAT((fTemp278 * fTemp281));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec12[1] = fRec12[0];
			fRec27[1] = fRec27[0];
			IOTA = (IOTA + 1);
			fRec28[1] = fRec28[0];
			fVec2[1] = fVec2[0];
			fRec29[1] = fRec29[0];
			fRec26[1] = fRec26[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fVec3[1] = fVec3[0];
			fRec30[1] = fRec30[0];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec31[1] = fRec31[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			iRec37[1] = iRec37[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec38[1] = fRec38[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fRec17[1] = fRec17[0];
			fRec15[1] = fRec15[0];
			fRec45[1] = fRec45[0];
			fRec43[1] = fRec43[0];
			fRec41[1] = fRec41[0];
			fRec39[1] = fRec39[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec50[1] = fRec50[0];
			fRec13[1] = fRec13[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fRec1[1] = fRec1[0];
			fRec64[1] = fRec64[0];
			fRec62[1] = fRec62[0];
			fRec60[1] = fRec60[0];
			fRec58[1] = fRec58[0];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec51[1] = fRec51[0];
			fRec2[1] = fRec2[0];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec69[1] = fRec69[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_CLASS_NAME "mydsp"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 10
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("High Cut", fHslider5, 1.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Low Cut", fHslider6, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("colour", fHslider2, 0.10000000000000001f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("decay", fHslider1, 0.29999999999999999f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("drag", fHslider9, 0.5f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("lag", fHslider4, 0.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modulate", fHslider7, 0.02f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("push", fHslider3, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("smear", fHslider8, 0.5f, 0.0f, 1.0f, 0.001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, High_Cut, "High Cut", fHslider5, 1.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Low_Cut, "Low Cut", fHslider6, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, colour, "colour", fHslider2, 0.10000000000000001f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, decay, "decay", fHslider1, 0.29999999999999999f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, drag, "drag", fHslider9, 0.5f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, lag, "lag", fHslider4, 0.0f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, mix, "mix", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, modulate, "modulate", fHslider7, 0.02f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, push, "push", fHslider3, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, smear, "smear", fHslider8, 0.5f, 0.0f, 1.0f, 0.001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#define MULT_16 2147483647
#define DIV_16 4.6566129e-10

unsigned __exidx_start;
unsigned __exidx_end;

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

mooSpace::mooSpace() : AudioStream(FAUST_INPUTS, new audio_block_t*[FAUST_INPUTS])
{
    fDSP = new mydsp();
    fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
    
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    // allocating Faust inputs
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fInChannel = NULL;
    }
    
    // allocating Faust outputs
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fOutChannel = NULL;
    }
    
#if MIDICTRL
    fMIDIHandler = new teensy_midi();
    fMIDIInterface = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIInterface);
    fMIDIInterface->run();
#endif
}

mooSpace::~mooSpace()
{
    delete fDSP;
    delete fUI;
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
#if MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

template <int INPUTS, int OUTPUTS>
void mooSpace::updateImp(void)
{
#if MIDICTRL
    // Process the MIDI messages received by the Teensy
    fMIDIHandler->processMidi();
    // Synchronize all GUI controllers
    GUI::updateAllGuis();
#endif
    
    if (INPUTS > 0) {
        audio_block_t* inBlock[INPUTS];
        for(int channel = 0; channel < INPUTS; channel++) {
            inBlock[channel] = receiveReadOnly(channel);
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                int32_t val = inBlock[channel]->data[i] << 16;
                fInChannel[channel][i] = val*DIV_16;
            }
            release(inBlock[channel]);
        }
    }
    
    fDSP->compute(AUDIO_BLOCK_SAMPLES, fInChannel, fOutChannel);
    
    for (int channel = 0; channel < OUTPUTS; channel++) {
        audio_block_t* outBlock[OUTPUTS];
        outBlock[channel] = allocate();
        if (outBlock[channel]) {
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                int32_t val = fOutChannel[channel][i]*MULT_16;
                outBlock[channel]->data[i] = val >> 16;
            }
            transmit(outBlock[channel], channel);
            release(outBlock[channel]);
        }
    }
}

void mooSpace::update(void) { updateImp<FAUST_INPUTS, FAUST_OUTPUTS>(); }

void mooSpace::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

float mooSpace::getParamValue(const std::string& path)
{
    return fUI->getParamValue(path);
}

#endif
