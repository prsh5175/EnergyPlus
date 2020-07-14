// EnergyPlus, Copyright (c) 1996-2020, The Board of Trustees of the University of Illinois,
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

#include <EnergyPlus/api/autosizing.h>
#include <EnergyPlus/Autosizing/HeatingAirflowUASizing.hh>
#include <EnergyPlus/DataSizing.hh>

char * getLastErrorMessages(Sizer sizer) {
    auto s = reinterpret_cast<EnergyPlus::BaseSizer *>(sizer);
    std::string const msg = s->getLastErrorMessages();
    // note that we cannot just return a c_str to the local string, as the string will be destructed upon leaving
    // this function, and undefined behavior will occur.
    // instead make a deep copy, and the user must manage the new char * pointer
    char *p = new char[std::strlen(msg.c_str())];
    std::strcpy(p, msg.c_str());
    return p;
}

Sizer sizerHeatingAirflowUANew() {
    auto sizer = new EnergyPlus::HeatingAirflowUASizer();
    return reinterpret_cast<Sizer>(sizer);
}
void sizerHeatingAirflowUADelete(Sizer sizer) {
    delete reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
}
void sizerHeatingAirflowUAInitializeForSingleDuctZoneTerminal(Sizer sizer, Real64 elevation, Real64 mainFlowRate) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSingleDuctZoneTerminal(elevation, mainFlowRate);
}
void sizerHeatingAirflowUAInitializeForZoneInductionUnit(Sizer sizer, Real64 elevation, Real64 mainFlowRate, Real64 reheatMultiplier) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForZoneInductionUnit(elevation, mainFlowRate, reheatMultiplier);
}
void sizerHeatingAirflowUAInitializeForZoneFanCoil(Sizer sizer, Real64 elevation, Real64 designHeatVolumeFlowRate) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForZoneFanCoil(elevation, designHeatVolumeFlowRate);
}
void sizerHeatingAirflowUAInitializeForSystemOutdoorAir(Sizer sizer, Real64 elevation, Real64 overallSystemMassFlowRate, int DOAS) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSystemOutdoorAir(elevation, overallSystemMassFlowRate, DOAS == 1); // TODO: Verify true/false 0/1 status here
}
void sizerHeatingAirflowUAInitializeForSystemMainDuct(Sizer sizer, Real64 elevation, Real64 overallSystemVolFlow, Real64 minFlowRateRatio) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSystemMainDuct(elevation, overallSystemVolFlow, minFlowRateRatio);
}
void sizerHeatingAirflowUAInitializeForSystemCoolingDuct(Sizer sizer, Real64 elevation) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSystemCoolingDuct(elevation);
}
void sizerHeatingAirflowUAInitializeForSystemHeatingDuct(Sizer sizer, Real64 elevation) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSystemHeatingDuct(elevation);
}
void sizerHeatingAirflowUAInitializeForSystemOtherDuct(Sizer sizer, Real64 elevation) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    s->initializeForSystemOtherDuct(elevation);
}
int sizerHeatingAirflowUACalculate(Sizer sizer) {
    auto s = reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer);
    bool errorsFound = false;
    s->size(EnergyPlus::DataSizing::AutoSize, errorsFound);
    if (errorsFound) {
        return 1;
    }
    return 0;
}
Real64 sizerHeatingAirflowUAValue(Sizer sizer) {
    return reinterpret_cast<EnergyPlus::HeatingAirflowUASizer *>(sizer)->autoSizedValue;
}
