// EnergyPlus, Copyright (c) 1996-2017, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef PVWatts_hh_INCLUDED
#define PVWatts_hh_INCLUDED

// C++ Headers
#include <string>
#include <map>

// ObjexxFCL Headers

// EnergyPlus Headers
#include <EnergyPlus.hh>
#include <DataSurfaces.hh>

namespace EnergyPlus {

namespace PVWatts {
    
    enum class ModuleType {
        STANDARD,
        PREMIUM,
        THIN_FILM,
    };
    
    enum class ArrayType {
        FIXED_OPEN_RACK,
        FIXED_ROOF_MOUNTED,
        ONE_AXIS,
        ONE_AXIS_BACKTRACKING,
        TWO_AXIS,
    };
    
    enum class GeometryType {
        TILT_AZIMUTH,
        SURFACE,
    };
    
    class PVWattsGenerator
    {
    private:

        enum AlphaFields {
            NAME = 1,
            VERSION = 2,
            MODULE_TYPE = 3,
            ARRAY_TYPE = 4,
            GEOMETRY_TYPE = 5,
            SURFACE_NAME = 6,
        };

        enum NumFields {
            DC_SYSTEM_CAPACITY = 1,
            SYSTEM_LOSSES = 2,
            TILT_ANGLE = 3,
            AZIMUTH_ANGLE = 4,
            GROUND_COVERAGE_RATIO = 5,
        };
        
        std::string m_name;
        Real64 m_dcSystemCapacity;
        ModuleType m_moduleType;
        ArrayType m_arrayType;
        Real64 m_systemLosses;
        GeometryType m_geometryType;
        Real64 m_tilt;
        Real64 m_azimuth;
        int m_surfaceNum;
        Real64 m_groundCoverageRatio;

        

        
    public:
        static PVWattsGenerator createFromIdfObj(int objNum);
        
        PVWattsGenerator(const std::string &name, const Real64 dcSystemCapacity, ModuleType moduleType, ArrayType arrayType, Real64 systemLosses=0.14, GeometryType geometryType=GeometryType::TILT_AZIMUTH, Real64 tilt=20.0, Real64 azimuth=180.0, size_t surfaceNum=0, Real64 groundCoverageRatio=0.4);
        
        Real64 getDCSystemCapacity();
        ModuleType getModuleType();
        ArrayType getArrayType();
        Real64 getSystemLosses();
        GeometryType getGeometryType();
        Real64 getTilt();
        Real64 getAzimuth();
        DataSurfaces::SurfaceData& getSurface();
        Real64 getGroundCoverageRatio();
        
    };
    
    extern std::map<std::string, PVWattsGenerator> PVWattsGenerators;
    
}

}

#endif
