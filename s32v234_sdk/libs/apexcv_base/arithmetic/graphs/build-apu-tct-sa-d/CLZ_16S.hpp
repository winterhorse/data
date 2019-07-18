#ifndef _ACF_PROCESS_APU_CLZ_16S
#define _ACF_PROCESS_APU_CLZ_16S

#include <acf_process_apu.h>
#include <apex_launcher.hpp>
#include <stdint.h>

#include <CLZ_16S_APU_LOAD.h> //APU load associated with this process

//SCENARIO LIST*************************************************
static acf_scenario_buffer_data gScenarioBufferData0_CLZ_16S[] = {{2, 1, 2, 0, {0, 0, 0, 0}}, {2, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData1_CLZ_16S[] = {{4, 1, 2, 0, {0, 0, 0, 0}}, {4, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData2_CLZ_16S[] = {{6, 1, 2, 0, {0, 0, 0, 0}}, {6, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData3_CLZ_16S[] = {{8, 1, 2, 0, {0, 0, 0, 0}}, {8, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData4_CLZ_16S[] = {{10, 1, 2, 0, {0, 0, 0, 0}}, {10, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData5_CLZ_16S[] = {{12, 1, 2, 0, {0, 0, 0, 0}}, {12, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData6_CLZ_16S[] = {{14, 1, 2, 0, {0, 0, 0, 0}}, {14, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData7_CLZ_16S[] = {{16, 1, 2, 0, {0, 0, 0, 0}}, {16, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData8_CLZ_16S[] = {{18, 1, 2, 0, {0, 0, 0, 0}}, {18, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData9_CLZ_16S[] = {{20, 1, 2, 0, {0, 0, 0, 0}}, {20, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData10_CLZ_16S[] = {{22, 1, 2, 0, {0, 0, 0, 0}}, {22, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData11_CLZ_16S[] = {{24, 1, 2, 0, {0, 0, 0, 0}}, {24, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData12_CLZ_16S[] = {{26, 1, 2, 0, {0, 0, 0, 0}}, {26, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData13_CLZ_16S[] = {{28, 1, 2, 0, {0, 0, 0, 0}}, {28, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData14_CLZ_16S[] = {{30, 1, 2, 0, {0, 0, 0, 0}}, {30, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData15_CLZ_16S[] = {{32, 1, 2, 0, {0, 0, 0, 0}}, {32, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData16_CLZ_16S[] = {{36, 1, 2, 0, {0, 0, 0, 0}}, {36, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData17_CLZ_16S[] = {{40, 1, 2, 0, {0, 0, 0, 0}}, {40, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData18_CLZ_16S[] = {{44, 1, 2, 0, {0, 0, 0, 0}}, {44, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData19_CLZ_16S[] = {{48, 1, 2, 0, {0, 0, 0, 0}}, {48, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData20_CLZ_16S[] = {{52, 1, 2, 0, {0, 0, 0, 0}}, {52, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData21_CLZ_16S[] = {{56, 1, 2, 0, {0, 0, 0, 0}}, {56, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData22_CLZ_16S[] = {{60, 1, 2, 0, {0, 0, 0, 0}}, {60, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData23_CLZ_16S[] = {{64, 1, 2, 0, {0, 0, 0, 0}}, {64, 1, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData24_CLZ_16S[] = {{2, 2, 2, 0, {0, 0, 0, 0}}, {2, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData25_CLZ_16S[] = {{4, 2, 2, 0, {0, 0, 0, 0}}, {4, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData26_CLZ_16S[] = {{6, 2, 2, 0, {0, 0, 0, 0}}, {6, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData27_CLZ_16S[] = {{8, 2, 2, 0, {0, 0, 0, 0}}, {8, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData28_CLZ_16S[] = {{10, 2, 2, 0, {0, 0, 0, 0}}, {10, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData29_CLZ_16S[] = {{12, 2, 2, 0, {0, 0, 0, 0}}, {12, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData30_CLZ_16S[] = {{14, 2, 2, 0, {0, 0, 0, 0}}, {14, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData31_CLZ_16S[] = {{16, 2, 2, 0, {0, 0, 0, 0}}, {16, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData32_CLZ_16S[] = {{18, 2, 2, 0, {0, 0, 0, 0}}, {18, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData33_CLZ_16S[] = {{20, 2, 2, 0, {0, 0, 0, 0}}, {20, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData34_CLZ_16S[] = {{22, 2, 2, 0, {0, 0, 0, 0}}, {22, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData35_CLZ_16S[] = {{24, 2, 2, 0, {0, 0, 0, 0}}, {24, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData36_CLZ_16S[] = {{26, 2, 2, 0, {0, 0, 0, 0}}, {26, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData37_CLZ_16S[] = {{28, 2, 2, 0, {0, 0, 0, 0}}, {28, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData38_CLZ_16S[] = {{30, 2, 2, 0, {0, 0, 0, 0}}, {30, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData39_CLZ_16S[] = {{32, 2, 2, 0, {0, 0, 0, 0}}, {32, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData40_CLZ_16S[] = {{36, 2, 2, 0, {0, 0, 0, 0}}, {36, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData41_CLZ_16S[] = {{40, 2, 2, 0, {0, 0, 0, 0}}, {40, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData42_CLZ_16S[] = {{44, 2, 2, 0, {0, 0, 0, 0}}, {44, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData43_CLZ_16S[] = {{48, 2, 2, 0, {0, 0, 0, 0}}, {48, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData44_CLZ_16S[] = {{52, 2, 2, 0, {0, 0, 0, 0}}, {52, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData45_CLZ_16S[] = {{56, 2, 2, 0, {0, 0, 0, 0}}, {56, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData46_CLZ_16S[] = {{60, 2, 2, 0, {0, 0, 0, 0}}, {60, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData47_CLZ_16S[] = {{64, 2, 2, 0, {0, 0, 0, 0}}, {64, 2, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData48_CLZ_16S[] = {{2, 3, 2, 0, {0, 0, 0, 0}}, {2, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData49_CLZ_16S[] = {{4, 3, 2, 0, {0, 0, 0, 0}}, {4, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData50_CLZ_16S[] = {{6, 3, 2, 0, {0, 0, 0, 0}}, {6, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData51_CLZ_16S[] = {{8, 3, 2, 0, {0, 0, 0, 0}}, {8, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData52_CLZ_16S[] = {{10, 3, 2, 0, {0, 0, 0, 0}}, {10, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData53_CLZ_16S[] = {{12, 3, 2, 0, {0, 0, 0, 0}}, {12, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData54_CLZ_16S[] = {{14, 3, 2, 0, {0, 0, 0, 0}}, {14, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData55_CLZ_16S[] = {{16, 3, 2, 0, {0, 0, 0, 0}}, {16, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData56_CLZ_16S[] = {{18, 3, 2, 0, {0, 0, 0, 0}}, {18, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData57_CLZ_16S[] = {{20, 3, 2, 0, {0, 0, 0, 0}}, {20, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData58_CLZ_16S[] = {{22, 3, 2, 0, {0, 0, 0, 0}}, {22, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData59_CLZ_16S[] = {{24, 3, 2, 0, {0, 0, 0, 0}}, {24, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData60_CLZ_16S[] = {{26, 3, 2, 0, {0, 0, 0, 0}}, {26, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData61_CLZ_16S[] = {{28, 3, 2, 0, {0, 0, 0, 0}}, {28, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData62_CLZ_16S[] = {{30, 3, 2, 0, {0, 0, 0, 0}}, {30, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData63_CLZ_16S[] = {{32, 3, 2, 0, {0, 0, 0, 0}}, {32, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData64_CLZ_16S[] = {{36, 3, 2, 0, {0, 0, 0, 0}}, {36, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData65_CLZ_16S[] = {{40, 3, 2, 0, {0, 0, 0, 0}}, {40, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData66_CLZ_16S[] = {{44, 3, 2, 0, {0, 0, 0, 0}}, {44, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData67_CLZ_16S[] = {{48, 3, 2, 0, {0, 0, 0, 0}}, {48, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData68_CLZ_16S[] = {{52, 3, 2, 0, {0, 0, 0, 0}}, {52, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData69_CLZ_16S[] = {{56, 3, 2, 0, {0, 0, 0, 0}}, {56, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData70_CLZ_16S[] = {{60, 3, 2, 0, {0, 0, 0, 0}}, {60, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData71_CLZ_16S[] = {{64, 3, 2, 0, {0, 0, 0, 0}}, {64, 3, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData72_CLZ_16S[] = {{2, 4, 2, 0, {0, 0, 0, 0}}, {2, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData73_CLZ_16S[] = {{4, 4, 2, 0, {0, 0, 0, 0}}, {4, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData74_CLZ_16S[] = {{6, 4, 2, 0, {0, 0, 0, 0}}, {6, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData75_CLZ_16S[] = {{8, 4, 2, 0, {0, 0, 0, 0}}, {8, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData76_CLZ_16S[] = {{10, 4, 2, 0, {0, 0, 0, 0}}, {10, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData77_CLZ_16S[] = {{12, 4, 2, 0, {0, 0, 0, 0}}, {12, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData78_CLZ_16S[] = {{14, 4, 2, 0, {0, 0, 0, 0}}, {14, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData79_CLZ_16S[] = {{16, 4, 2, 0, {0, 0, 0, 0}}, {16, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData80_CLZ_16S[] = {{18, 4, 2, 0, {0, 0, 0, 0}}, {18, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData81_CLZ_16S[] = {{20, 4, 2, 0, {0, 0, 0, 0}}, {20, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData82_CLZ_16S[] = {{22, 4, 2, 0, {0, 0, 0, 0}}, {22, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData83_CLZ_16S[] = {{24, 4, 2, 0, {0, 0, 0, 0}}, {24, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData84_CLZ_16S[] = {{26, 4, 2, 0, {0, 0, 0, 0}}, {26, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData85_CLZ_16S[] = {{28, 4, 2, 0, {0, 0, 0, 0}}, {28, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData86_CLZ_16S[] = {{30, 4, 2, 0, {0, 0, 0, 0}}, {30, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData87_CLZ_16S[] = {{32, 4, 2, 0, {0, 0, 0, 0}}, {32, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData88_CLZ_16S[] = {{36, 4, 2, 0, {0, 0, 0, 0}}, {36, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData89_CLZ_16S[] = {{40, 4, 2, 0, {0, 0, 0, 0}}, {40, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData90_CLZ_16S[] = {{44, 4, 2, 0, {0, 0, 0, 0}}, {44, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData91_CLZ_16S[] = {{48, 4, 2, 0, {0, 0, 0, 0}}, {48, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData92_CLZ_16S[] = {{52, 4, 2, 0, {0, 0, 0, 0}}, {52, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData93_CLZ_16S[] = {{56, 4, 2, 0, {0, 0, 0, 0}}, {56, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData94_CLZ_16S[] = {{60, 4, 2, 0, {0, 0, 0, 0}}, {60, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData95_CLZ_16S[] = {{64, 4, 2, 0, {0, 0, 0, 0}}, {64, 4, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData96_CLZ_16S[] = {{2, 5, 2, 0, {0, 0, 0, 0}}, {2, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData97_CLZ_16S[] = {{4, 5, 2, 0, {0, 0, 0, 0}}, {4, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData98_CLZ_16S[] = {{6, 5, 2, 0, {0, 0, 0, 0}}, {6, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData99_CLZ_16S[] = {{8, 5, 2, 0, {0, 0, 0, 0}}, {8, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData100_CLZ_16S[] = {{10, 5, 2, 0, {0, 0, 0, 0}}, {10, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData101_CLZ_16S[] = {{12, 5, 2, 0, {0, 0, 0, 0}}, {12, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData102_CLZ_16S[] = {{14, 5, 2, 0, {0, 0, 0, 0}}, {14, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData103_CLZ_16S[] = {{16, 5, 2, 0, {0, 0, 0, 0}}, {16, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData104_CLZ_16S[] = {{18, 5, 2, 0, {0, 0, 0, 0}}, {18, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData105_CLZ_16S[] = {{20, 5, 2, 0, {0, 0, 0, 0}}, {20, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData106_CLZ_16S[] = {{22, 5, 2, 0, {0, 0, 0, 0}}, {22, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData107_CLZ_16S[] = {{24, 5, 2, 0, {0, 0, 0, 0}}, {24, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData108_CLZ_16S[] = {{26, 5, 2, 0, {0, 0, 0, 0}}, {26, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData109_CLZ_16S[] = {{28, 5, 2, 0, {0, 0, 0, 0}}, {28, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData110_CLZ_16S[] = {{30, 5, 2, 0, {0, 0, 0, 0}}, {30, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData111_CLZ_16S[] = {{32, 5, 2, 0, {0, 0, 0, 0}}, {32, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData112_CLZ_16S[] = {{36, 5, 2, 0, {0, 0, 0, 0}}, {36, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData113_CLZ_16S[] = {{40, 5, 2, 0, {0, 0, 0, 0}}, {40, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData114_CLZ_16S[] = {{44, 5, 2, 0, {0, 0, 0, 0}}, {44, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData115_CLZ_16S[] = {{48, 5, 2, 0, {0, 0, 0, 0}}, {48, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData116_CLZ_16S[] = {{52, 5, 2, 0, {0, 0, 0, 0}}, {52, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData117_CLZ_16S[] = {{56, 5, 2, 0, {0, 0, 0, 0}}, {56, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData118_CLZ_16S[] = {{60, 5, 2, 0, {0, 0, 0, 0}}, {60, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData119_CLZ_16S[] = {{64, 5, 2, 0, {0, 0, 0, 0}}, {64, 5, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData120_CLZ_16S[] = {{2, 6, 2, 0, {0, 0, 0, 0}}, {2, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData121_CLZ_16S[] = {{4, 6, 2, 0, {0, 0, 0, 0}}, {4, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData122_CLZ_16S[] = {{6, 6, 2, 0, {0, 0, 0, 0}}, {6, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData123_CLZ_16S[] = {{8, 6, 2, 0, {0, 0, 0, 0}}, {8, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData124_CLZ_16S[] = {{10, 6, 2, 0, {0, 0, 0, 0}}, {10, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData125_CLZ_16S[] = {{12, 6, 2, 0, {0, 0, 0, 0}}, {12, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData126_CLZ_16S[] = {{14, 6, 2, 0, {0, 0, 0, 0}}, {14, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData127_CLZ_16S[] = {{16, 6, 2, 0, {0, 0, 0, 0}}, {16, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData128_CLZ_16S[] = {{18, 6, 2, 0, {0, 0, 0, 0}}, {18, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData129_CLZ_16S[] = {{20, 6, 2, 0, {0, 0, 0, 0}}, {20, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData130_CLZ_16S[] = {{22, 6, 2, 0, {0, 0, 0, 0}}, {22, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData131_CLZ_16S[] = {{24, 6, 2, 0, {0, 0, 0, 0}}, {24, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData132_CLZ_16S[] = {{26, 6, 2, 0, {0, 0, 0, 0}}, {26, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData133_CLZ_16S[] = {{28, 6, 2, 0, {0, 0, 0, 0}}, {28, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData134_CLZ_16S[] = {{30, 6, 2, 0, {0, 0, 0, 0}}, {30, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData135_CLZ_16S[] = {{32, 6, 2, 0, {0, 0, 0, 0}}, {32, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData136_CLZ_16S[] = {{36, 6, 2, 0, {0, 0, 0, 0}}, {36, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData137_CLZ_16S[] = {{40, 6, 2, 0, {0, 0, 0, 0}}, {40, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData138_CLZ_16S[] = {{44, 6, 2, 0, {0, 0, 0, 0}}, {44, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData139_CLZ_16S[] = {{48, 6, 2, 0, {0, 0, 0, 0}}, {48, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData140_CLZ_16S[] = {{52, 6, 2, 0, {0, 0, 0, 0}}, {52, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData141_CLZ_16S[] = {{56, 6, 2, 0, {0, 0, 0, 0}}, {56, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData142_CLZ_16S[] = {{60, 6, 2, 0, {0, 0, 0, 0}}, {60, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData143_CLZ_16S[] = {{64, 6, 2, 0, {0, 0, 0, 0}}, {64, 6, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData144_CLZ_16S[] = {{2, 8, 2, 0, {0, 0, 0, 0}}, {2, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData145_CLZ_16S[] = {{4, 8, 2, 0, {0, 0, 0, 0}}, {4, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData146_CLZ_16S[] = {{6, 8, 2, 0, {0, 0, 0, 0}}, {6, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData147_CLZ_16S[] = {{8, 8, 2, 0, {0, 0, 0, 0}}, {8, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData148_CLZ_16S[] = {{10, 8, 2, 0, {0, 0, 0, 0}}, {10, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData149_CLZ_16S[] = {{12, 8, 2, 0, {0, 0, 0, 0}}, {12, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData150_CLZ_16S[] = {{14, 8, 2, 0, {0, 0, 0, 0}}, {14, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData151_CLZ_16S[] = {{16, 8, 2, 0, {0, 0, 0, 0}}, {16, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData152_CLZ_16S[] = {{18, 8, 2, 0, {0, 0, 0, 0}}, {18, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData153_CLZ_16S[] = {{20, 8, 2, 0, {0, 0, 0, 0}}, {20, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData154_CLZ_16S[] = {{22, 8, 2, 0, {0, 0, 0, 0}}, {22, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData155_CLZ_16S[] = {{24, 8, 2, 0, {0, 0, 0, 0}}, {24, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData156_CLZ_16S[] = {{26, 8, 2, 0, {0, 0, 0, 0}}, {26, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData157_CLZ_16S[] = {{28, 8, 2, 0, {0, 0, 0, 0}}, {28, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData158_CLZ_16S[] = {{30, 8, 2, 0, {0, 0, 0, 0}}, {30, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData159_CLZ_16S[] = {{32, 8, 2, 0, {0, 0, 0, 0}}, {32, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData160_CLZ_16S[] = {{36, 8, 2, 0, {0, 0, 0, 0}}, {36, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData161_CLZ_16S[] = {{40, 8, 2, 0, {0, 0, 0, 0}}, {40, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData162_CLZ_16S[] = {{44, 8, 2, 0, {0, 0, 0, 0}}, {44, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData163_CLZ_16S[] = {{48, 8, 2, 0, {0, 0, 0, 0}}, {48, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData164_CLZ_16S[] = {{52, 8, 2, 0, {0, 0, 0, 0}}, {52, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData165_CLZ_16S[] = {{56, 8, 2, 0, {0, 0, 0, 0}}, {56, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData166_CLZ_16S[] = {{60, 8, 2, 0, {0, 0, 0, 0}}, {60, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData167_CLZ_16S[] = {{64, 8, 2, 0, {0, 0, 0, 0}}, {64, 8, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData168_CLZ_16S[] = {{2, 10, 2, 0, {0, 0, 0, 0}}, {2, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData169_CLZ_16S[] = {{4, 10, 2, 0, {0, 0, 0, 0}}, {4, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData170_CLZ_16S[] = {{6, 10, 2, 0, {0, 0, 0, 0}}, {6, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData171_CLZ_16S[] = {{8, 10, 2, 0, {0, 0, 0, 0}}, {8, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData172_CLZ_16S[] = {{10, 10, 2, 0, {0, 0, 0, 0}}, {10, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData173_CLZ_16S[] = {{12, 10, 2, 0, {0, 0, 0, 0}}, {12, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData174_CLZ_16S[] = {{14, 10, 2, 0, {0, 0, 0, 0}}, {14, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData175_CLZ_16S[] = {{16, 10, 2, 0, {0, 0, 0, 0}}, {16, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData176_CLZ_16S[] = {{18, 10, 2, 0, {0, 0, 0, 0}}, {18, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData177_CLZ_16S[] = {{20, 10, 2, 0, {0, 0, 0, 0}}, {20, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData178_CLZ_16S[] = {{22, 10, 2, 0, {0, 0, 0, 0}}, {22, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData179_CLZ_16S[] = {{24, 10, 2, 0, {0, 0, 0, 0}}, {24, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData180_CLZ_16S[] = {{26, 10, 2, 0, {0, 0, 0, 0}}, {26, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData181_CLZ_16S[] = {{28, 10, 2, 0, {0, 0, 0, 0}}, {28, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData182_CLZ_16S[] = {{30, 10, 2, 0, {0, 0, 0, 0}}, {30, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData183_CLZ_16S[] = {{32, 10, 2, 0, {0, 0, 0, 0}}, {32, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData184_CLZ_16S[] = {{36, 10, 2, 0, {0, 0, 0, 0}}, {36, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData185_CLZ_16S[] = {{40, 10, 2, 0, {0, 0, 0, 0}}, {40, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData186_CLZ_16S[] = {{44, 10, 2, 0, {0, 0, 0, 0}}, {44, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData187_CLZ_16S[] = {{48, 10, 2, 0, {0, 0, 0, 0}}, {48, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData188_CLZ_16S[] = {{52, 10, 2, 0, {0, 0, 0, 0}}, {52, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData189_CLZ_16S[] = {{56, 10, 2, 0, {0, 0, 0, 0}}, {56, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData190_CLZ_16S[] = {{60, 10, 2, 0, {0, 0, 0, 0}}, {60, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData191_CLZ_16S[] = {{64, 10, 2, 0, {0, 0, 0, 0}}, {64, 10, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData192_CLZ_16S[] = {{2, 12, 2, 0, {0, 0, 0, 0}}, {2, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData193_CLZ_16S[] = {{4, 12, 2, 0, {0, 0, 0, 0}}, {4, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData194_CLZ_16S[] = {{6, 12, 2, 0, {0, 0, 0, 0}}, {6, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData195_CLZ_16S[] = {{8, 12, 2, 0, {0, 0, 0, 0}}, {8, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData196_CLZ_16S[] = {{10, 12, 2, 0, {0, 0, 0, 0}}, {10, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData197_CLZ_16S[] = {{12, 12, 2, 0, {0, 0, 0, 0}}, {12, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData198_CLZ_16S[] = {{14, 12, 2, 0, {0, 0, 0, 0}}, {14, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData199_CLZ_16S[] = {{16, 12, 2, 0, {0, 0, 0, 0}}, {16, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData200_CLZ_16S[] = {{18, 12, 2, 0, {0, 0, 0, 0}}, {18, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData201_CLZ_16S[] = {{20, 12, 2, 0, {0, 0, 0, 0}}, {20, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData202_CLZ_16S[] = {{22, 12, 2, 0, {0, 0, 0, 0}}, {22, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData203_CLZ_16S[] = {{24, 12, 2, 0, {0, 0, 0, 0}}, {24, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData204_CLZ_16S[] = {{26, 12, 2, 0, {0, 0, 0, 0}}, {26, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData205_CLZ_16S[] = {{28, 12, 2, 0, {0, 0, 0, 0}}, {28, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData206_CLZ_16S[] = {{30, 12, 2, 0, {0, 0, 0, 0}}, {30, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData207_CLZ_16S[] = {{32, 12, 2, 0, {0, 0, 0, 0}}, {32, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData208_CLZ_16S[] = {{36, 12, 2, 0, {0, 0, 0, 0}}, {36, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData209_CLZ_16S[] = {{40, 12, 2, 0, {0, 0, 0, 0}}, {40, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData210_CLZ_16S[] = {{44, 12, 2, 0, {0, 0, 0, 0}}, {44, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData211_CLZ_16S[] = {{48, 12, 2, 0, {0, 0, 0, 0}}, {48, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData212_CLZ_16S[] = {{52, 12, 2, 0, {0, 0, 0, 0}}, {52, 12, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData213_CLZ_16S[] = {{2, 14, 2, 0, {0, 0, 0, 0}}, {2, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData214_CLZ_16S[] = {{4, 14, 2, 0, {0, 0, 0, 0}}, {4, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData215_CLZ_16S[] = {{6, 14, 2, 0, {0, 0, 0, 0}}, {6, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData216_CLZ_16S[] = {{8, 14, 2, 0, {0, 0, 0, 0}}, {8, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData217_CLZ_16S[] = {{10, 14, 2, 0, {0, 0, 0, 0}}, {10, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData218_CLZ_16S[] = {{12, 14, 2, 0, {0, 0, 0, 0}}, {12, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData219_CLZ_16S[] = {{14, 14, 2, 0, {0, 0, 0, 0}}, {14, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData220_CLZ_16S[] = {{16, 14, 2, 0, {0, 0, 0, 0}}, {16, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData221_CLZ_16S[] = {{18, 14, 2, 0, {0, 0, 0, 0}}, {18, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData222_CLZ_16S[] = {{20, 14, 2, 0, {0, 0, 0, 0}}, {20, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData223_CLZ_16S[] = {{22, 14, 2, 0, {0, 0, 0, 0}}, {22, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData224_CLZ_16S[] = {{24, 14, 2, 0, {0, 0, 0, 0}}, {24, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData225_CLZ_16S[] = {{26, 14, 2, 0, {0, 0, 0, 0}}, {26, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData226_CLZ_16S[] = {{28, 14, 2, 0, {0, 0, 0, 0}}, {28, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData227_CLZ_16S[] = {{30, 14, 2, 0, {0, 0, 0, 0}}, {30, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData228_CLZ_16S[] = {{32, 14, 2, 0, {0, 0, 0, 0}}, {32, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData229_CLZ_16S[] = {{36, 14, 2, 0, {0, 0, 0, 0}}, {36, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData230_CLZ_16S[] = {{40, 14, 2, 0, {0, 0, 0, 0}}, {40, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData231_CLZ_16S[] = {{44, 14, 2, 0, {0, 0, 0, 0}}, {44, 14, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData232_CLZ_16S[] = {{2, 16, 2, 0, {0, 0, 0, 0}}, {2, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData233_CLZ_16S[] = {{4, 16, 2, 0, {0, 0, 0, 0}}, {4, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData234_CLZ_16S[] = {{6, 16, 2, 0, {0, 0, 0, 0}}, {6, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData235_CLZ_16S[] = {{8, 16, 2, 0, {0, 0, 0, 0}}, {8, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData236_CLZ_16S[] = {{10, 16, 2, 0, {0, 0, 0, 0}}, {10, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData237_CLZ_16S[] = {{12, 16, 2, 0, {0, 0, 0, 0}}, {12, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData238_CLZ_16S[] = {{14, 16, 2, 0, {0, 0, 0, 0}}, {14, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData239_CLZ_16S[] = {{16, 16, 2, 0, {0, 0, 0, 0}}, {16, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData240_CLZ_16S[] = {{18, 16, 2, 0, {0, 0, 0, 0}}, {18, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData241_CLZ_16S[] = {{20, 16, 2, 0, {0, 0, 0, 0}}, {20, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData242_CLZ_16S[] = {{22, 16, 2, 0, {0, 0, 0, 0}}, {22, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData243_CLZ_16S[] = {{24, 16, 2, 0, {0, 0, 0, 0}}, {24, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData244_CLZ_16S[] = {{26, 16, 2, 0, {0, 0, 0, 0}}, {26, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData245_CLZ_16S[] = {{28, 16, 2, 0, {0, 0, 0, 0}}, {28, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData246_CLZ_16S[] = {{30, 16, 2, 0, {0, 0, 0, 0}}, {30, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData247_CLZ_16S[] = {{32, 16, 2, 0, {0, 0, 0, 0}}, {32, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData248_CLZ_16S[] = {{36, 16, 2, 0, {0, 0, 0, 0}}, {36, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData249_CLZ_16S[] = {{40, 16, 2, 0, {0, 0, 0, 0}}, {40, 16, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData250_CLZ_16S[] = {{2, 18, 2, 0, {0, 0, 0, 0}}, {2, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData251_CLZ_16S[] = {{4, 18, 2, 0, {0, 0, 0, 0}}, {4, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData252_CLZ_16S[] = {{6, 18, 2, 0, {0, 0, 0, 0}}, {6, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData253_CLZ_16S[] = {{8, 18, 2, 0, {0, 0, 0, 0}}, {8, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData254_CLZ_16S[] = {{10, 18, 2, 0, {0, 0, 0, 0}}, {10, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData255_CLZ_16S[] = {{12, 18, 2, 0, {0, 0, 0, 0}}, {12, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData256_CLZ_16S[] = {{14, 18, 2, 0, {0, 0, 0, 0}}, {14, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData257_CLZ_16S[] = {{16, 18, 2, 0, {0, 0, 0, 0}}, {16, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData258_CLZ_16S[] = {{18, 18, 2, 0, {0, 0, 0, 0}}, {18, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData259_CLZ_16S[] = {{20, 18, 2, 0, {0, 0, 0, 0}}, {20, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData260_CLZ_16S[] = {{22, 18, 2, 0, {0, 0, 0, 0}}, {22, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData261_CLZ_16S[] = {{24, 18, 2, 0, {0, 0, 0, 0}}, {24, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData262_CLZ_16S[] = {{26, 18, 2, 0, {0, 0, 0, 0}}, {26, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData263_CLZ_16S[] = {{28, 18, 2, 0, {0, 0, 0, 0}}, {28, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData264_CLZ_16S[] = {{30, 18, 2, 0, {0, 0, 0, 0}}, {30, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData265_CLZ_16S[] = {{32, 18, 2, 0, {0, 0, 0, 0}}, {32, 18, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData266_CLZ_16S[] = {{2, 20, 2, 0, {0, 0, 0, 0}}, {2, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData267_CLZ_16S[] = {{4, 20, 2, 0, {0, 0, 0, 0}}, {4, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData268_CLZ_16S[] = {{6, 20, 2, 0, {0, 0, 0, 0}}, {6, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData269_CLZ_16S[] = {{8, 20, 2, 0, {0, 0, 0, 0}}, {8, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData270_CLZ_16S[] = {{10, 20, 2, 0, {0, 0, 0, 0}}, {10, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData271_CLZ_16S[] = {{12, 20, 2, 0, {0, 0, 0, 0}}, {12, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData272_CLZ_16S[] = {{14, 20, 2, 0, {0, 0, 0, 0}}, {14, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData273_CLZ_16S[] = {{16, 20, 2, 0, {0, 0, 0, 0}}, {16, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData274_CLZ_16S[] = {{18, 20, 2, 0, {0, 0, 0, 0}}, {18, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData275_CLZ_16S[] = {{20, 20, 2, 0, {0, 0, 0, 0}}, {20, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData276_CLZ_16S[] = {{22, 20, 2, 0, {0, 0, 0, 0}}, {22, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData277_CLZ_16S[] = {{24, 20, 2, 0, {0, 0, 0, 0}}, {24, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData278_CLZ_16S[] = {{26, 20, 2, 0, {0, 0, 0, 0}}, {26, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData279_CLZ_16S[] = {{28, 20, 2, 0, {0, 0, 0, 0}}, {28, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData280_CLZ_16S[] = {{30, 20, 2, 0, {0, 0, 0, 0}}, {30, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData281_CLZ_16S[] = {{32, 20, 2, 0, {0, 0, 0, 0}}, {32, 20, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData282_CLZ_16S[] = {{2, 22, 2, 0, {0, 0, 0, 0}}, {2, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData283_CLZ_16S[] = {{4, 22, 2, 0, {0, 0, 0, 0}}, {4, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData284_CLZ_16S[] = {{6, 22, 2, 0, {0, 0, 0, 0}}, {6, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData285_CLZ_16S[] = {{8, 22, 2, 0, {0, 0, 0, 0}}, {8, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData286_CLZ_16S[] = {{10, 22, 2, 0, {0, 0, 0, 0}}, {10, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData287_CLZ_16S[] = {{12, 22, 2, 0, {0, 0, 0, 0}}, {12, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData288_CLZ_16S[] = {{14, 22, 2, 0, {0, 0, 0, 0}}, {14, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData289_CLZ_16S[] = {{16, 22, 2, 0, {0, 0, 0, 0}}, {16, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData290_CLZ_16S[] = {{18, 22, 2, 0, {0, 0, 0, 0}}, {18, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData291_CLZ_16S[] = {{20, 22, 2, 0, {0, 0, 0, 0}}, {20, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData292_CLZ_16S[] = {{22, 22, 2, 0, {0, 0, 0, 0}}, {22, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData293_CLZ_16S[] = {{24, 22, 2, 0, {0, 0, 0, 0}}, {24, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData294_CLZ_16S[] = {{26, 22, 2, 0, {0, 0, 0, 0}}, {26, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData295_CLZ_16S[] = {{28, 22, 2, 0, {0, 0, 0, 0}}, {28, 22, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData296_CLZ_16S[] = {{2, 24, 2, 0, {0, 0, 0, 0}}, {2, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData297_CLZ_16S[] = {{4, 24, 2, 0, {0, 0, 0, 0}}, {4, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData298_CLZ_16S[] = {{6, 24, 2, 0, {0, 0, 0, 0}}, {6, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData299_CLZ_16S[] = {{8, 24, 2, 0, {0, 0, 0, 0}}, {8, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData300_CLZ_16S[] = {{10, 24, 2, 0, {0, 0, 0, 0}}, {10, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData301_CLZ_16S[] = {{12, 24, 2, 0, {0, 0, 0, 0}}, {12, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData302_CLZ_16S[] = {{14, 24, 2, 0, {0, 0, 0, 0}}, {14, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData303_CLZ_16S[] = {{16, 24, 2, 0, {0, 0, 0, 0}}, {16, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData304_CLZ_16S[] = {{18, 24, 2, 0, {0, 0, 0, 0}}, {18, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData305_CLZ_16S[] = {{20, 24, 2, 0, {0, 0, 0, 0}}, {20, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData306_CLZ_16S[] = {{22, 24, 2, 0, {0, 0, 0, 0}}, {22, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData307_CLZ_16S[] = {{24, 24, 2, 0, {0, 0, 0, 0}}, {24, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData308_CLZ_16S[] = {{26, 24, 2, 0, {0, 0, 0, 0}}, {26, 24, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData309_CLZ_16S[] = {{2, 26, 2, 0, {0, 0, 0, 0}}, {2, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData310_CLZ_16S[] = {{4, 26, 2, 0, {0, 0, 0, 0}}, {4, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData311_CLZ_16S[] = {{6, 26, 2, 0, {0, 0, 0, 0}}, {6, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData312_CLZ_16S[] = {{8, 26, 2, 0, {0, 0, 0, 0}}, {8, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData313_CLZ_16S[] = {{10, 26, 2, 0, {0, 0, 0, 0}}, {10, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData314_CLZ_16S[] = {{12, 26, 2, 0, {0, 0, 0, 0}}, {12, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData315_CLZ_16S[] = {{14, 26, 2, 0, {0, 0, 0, 0}}, {14, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData316_CLZ_16S[] = {{16, 26, 2, 0, {0, 0, 0, 0}}, {16, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData317_CLZ_16S[] = {{18, 26, 2, 0, {0, 0, 0, 0}}, {18, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData318_CLZ_16S[] = {{20, 26, 2, 0, {0, 0, 0, 0}}, {20, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData319_CLZ_16S[] = {{22, 26, 2, 0, {0, 0, 0, 0}}, {22, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData320_CLZ_16S[] = {{24, 26, 2, 0, {0, 0, 0, 0}}, {24, 26, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData321_CLZ_16S[] = {{2, 28, 2, 0, {0, 0, 0, 0}}, {2, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData322_CLZ_16S[] = {{4, 28, 2, 0, {0, 0, 0, 0}}, {4, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData323_CLZ_16S[] = {{6, 28, 2, 0, {0, 0, 0, 0}}, {6, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData324_CLZ_16S[] = {{8, 28, 2, 0, {0, 0, 0, 0}}, {8, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData325_CLZ_16S[] = {{10, 28, 2, 0, {0, 0, 0, 0}}, {10, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData326_CLZ_16S[] = {{12, 28, 2, 0, {0, 0, 0, 0}}, {12, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData327_CLZ_16S[] = {{14, 28, 2, 0, {0, 0, 0, 0}}, {14, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData328_CLZ_16S[] = {{16, 28, 2, 0, {0, 0, 0, 0}}, {16, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData329_CLZ_16S[] = {{18, 28, 2, 0, {0, 0, 0, 0}}, {18, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData330_CLZ_16S[] = {{20, 28, 2, 0, {0, 0, 0, 0}}, {20, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData331_CLZ_16S[] = {{22, 28, 2, 0, {0, 0, 0, 0}}, {22, 28, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData332_CLZ_16S[] = {{2, 30, 2, 0, {0, 0, 0, 0}}, {2, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData333_CLZ_16S[] = {{4, 30, 2, 0, {0, 0, 0, 0}}, {4, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData334_CLZ_16S[] = {{6, 30, 2, 0, {0, 0, 0, 0}}, {6, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData335_CLZ_16S[] = {{8, 30, 2, 0, {0, 0, 0, 0}}, {8, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData336_CLZ_16S[] = {{10, 30, 2, 0, {0, 0, 0, 0}}, {10, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData337_CLZ_16S[] = {{12, 30, 2, 0, {0, 0, 0, 0}}, {12, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData338_CLZ_16S[] = {{14, 30, 2, 0, {0, 0, 0, 0}}, {14, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData339_CLZ_16S[] = {{16, 30, 2, 0, {0, 0, 0, 0}}, {16, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData340_CLZ_16S[] = {{18, 30, 2, 0, {0, 0, 0, 0}}, {18, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData341_CLZ_16S[] = {{20, 30, 2, 0, {0, 0, 0, 0}}, {20, 30, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData342_CLZ_16S[] = {{2, 32, 2, 0, {0, 0, 0, 0}}, {2, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData343_CLZ_16S[] = {{4, 32, 2, 0, {0, 0, 0, 0}}, {4, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData344_CLZ_16S[] = {{6, 32, 2, 0, {0, 0, 0, 0}}, {6, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData345_CLZ_16S[] = {{8, 32, 2, 0, {0, 0, 0, 0}}, {8, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData346_CLZ_16S[] = {{10, 32, 2, 0, {0, 0, 0, 0}}, {10, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData347_CLZ_16S[] = {{12, 32, 2, 0, {0, 0, 0, 0}}, {12, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData348_CLZ_16S[] = {{14, 32, 2, 0, {0, 0, 0, 0}}, {14, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData349_CLZ_16S[] = {{16, 32, 2, 0, {0, 0, 0, 0}}, {16, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData350_CLZ_16S[] = {{18, 32, 2, 0, {0, 0, 0, 0}}, {18, 32, 2, 0, {0, 0, 0, 0}}};
static acf_scenario_buffer_data gScenarioBufferData351_CLZ_16S[] = {{20, 32, 2, 0, {0, 0, 0, 0}}, {20, 32, 2, 0, {0, 0, 0, 0}}};

static acf_scenario_kernel_data gScenarioKernelData0_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData1_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData2_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData3_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData4_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData5_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData6_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData7_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData8_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData9_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData10_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData11_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData12_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData13_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData14_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData15_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData16_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData17_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData18_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData19_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData20_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData21_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData22_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData23_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData24_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData25_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData26_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData27_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData28_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData29_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData30_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData31_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData32_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData33_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData34_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData35_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData36_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData37_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData38_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData39_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData40_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData41_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData42_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData43_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData44_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData45_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData46_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData47_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData48_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData49_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData50_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData51_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData52_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData53_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData54_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData55_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData56_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData57_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData58_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData59_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData60_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData61_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData62_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData63_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData64_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData65_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData66_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData67_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData68_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData69_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData70_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData71_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData72_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData73_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData74_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData75_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData76_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData77_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData78_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData79_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData80_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData81_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData82_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData83_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData84_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData85_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData86_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData87_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData88_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData89_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData90_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData91_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData92_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData93_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData94_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData95_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData96_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData97_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData98_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData99_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData100_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData101_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData102_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData103_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData104_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData105_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData106_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData107_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData108_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData109_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData110_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData111_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData112_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData113_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData114_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData115_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData116_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData117_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData118_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData119_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData120_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData121_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData122_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData123_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData124_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData125_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData126_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData127_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData128_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData129_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData130_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData131_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData132_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData133_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData134_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData135_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData136_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData137_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData138_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData139_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData140_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData141_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData142_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData143_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData144_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData145_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData146_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData147_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData148_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData149_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData150_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData151_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData152_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData153_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData154_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData155_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData156_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData157_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData158_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData159_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData160_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData161_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData162_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData163_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData164_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData165_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData166_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData167_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData168_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData169_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData170_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData171_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData172_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData173_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData174_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData175_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData176_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData177_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData178_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData179_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData180_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData181_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData182_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData183_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData184_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData185_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData186_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData187_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData188_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData189_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData190_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData191_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData192_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData193_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData194_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData195_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData196_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData197_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData198_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData199_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData200_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData201_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData202_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData203_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData204_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData205_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData206_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData207_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData208_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData209_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData210_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData211_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData212_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData213_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData214_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData215_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData216_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData217_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData218_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData219_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData220_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData221_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData222_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData223_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData224_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData225_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData226_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData227_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData228_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData229_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData230_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData231_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData232_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData233_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData234_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData235_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData236_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData237_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData238_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData239_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData240_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData241_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData242_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData243_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData244_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData245_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData246_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData247_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData248_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData249_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData250_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData251_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData252_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData253_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData254_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData255_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData256_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData257_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData258_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData259_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData260_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData261_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData262_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData263_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData264_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData265_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData266_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData267_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData268_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData269_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData270_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData271_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData272_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData273_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData274_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData275_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData276_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData277_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData278_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData279_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData280_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData281_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData282_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData283_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData284_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData285_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData286_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData287_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData288_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData289_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData290_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData291_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData292_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData293_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData294_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData295_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData296_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData297_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData298_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData299_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData300_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData301_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData302_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData303_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData304_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData305_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData306_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData307_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData308_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData309_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData310_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData311_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData312_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData313_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData314_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData315_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData316_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData317_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData318_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData319_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData320_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData321_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData322_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData323_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData324_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData325_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData326_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData327_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData328_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData329_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData330_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData331_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData332_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData333_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData334_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData335_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData336_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData337_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData338_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData339_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData340_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData341_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData342_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData343_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData344_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData345_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData346_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData347_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData348_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData349_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData350_CLZ_16S[] = {{0, 0}};
static acf_scenario_kernel_data gScenarioKernelData351_CLZ_16S[] = {{0, 0}};

static acf_scenario gScenarioArray_CLZ_16S[] = {
{2, 1, 12, 0, 0, gScenarioBufferData0_CLZ_16S, 32, gScenarioKernelData0_CLZ_16S, 4},
{4, 1, 24, 0, 0, gScenarioBufferData1_CLZ_16S, 32, gScenarioKernelData1_CLZ_16S, 4},
{6, 1, 36, 0, 0, gScenarioBufferData2_CLZ_16S, 32, gScenarioKernelData2_CLZ_16S, 4},
{8, 1, 48, 0, 0, gScenarioBufferData3_CLZ_16S, 32, gScenarioKernelData3_CLZ_16S, 4},
{10, 1, 60, 0, 0, gScenarioBufferData4_CLZ_16S, 32, gScenarioKernelData4_CLZ_16S, 4},
{12, 1, 72, 0, 0, gScenarioBufferData5_CLZ_16S, 32, gScenarioKernelData5_CLZ_16S, 4},
{14, 1, 84, 0, 0, gScenarioBufferData6_CLZ_16S, 32, gScenarioKernelData6_CLZ_16S, 4},
{16, 1, 96, 0, 0, gScenarioBufferData7_CLZ_16S, 32, gScenarioKernelData7_CLZ_16S, 4},
{18, 1, 108, 0, 0, gScenarioBufferData8_CLZ_16S, 32, gScenarioKernelData8_CLZ_16S, 4},
{20, 1, 120, 0, 0, gScenarioBufferData9_CLZ_16S, 32, gScenarioKernelData9_CLZ_16S, 4},
{22, 1, 132, 0, 0, gScenarioBufferData10_CLZ_16S, 32, gScenarioKernelData10_CLZ_16S, 4},
{24, 1, 144, 0, 0, gScenarioBufferData11_CLZ_16S, 32, gScenarioKernelData11_CLZ_16S, 4},
{26, 1, 156, 0, 0, gScenarioBufferData12_CLZ_16S, 32, gScenarioKernelData12_CLZ_16S, 4},
{28, 1, 168, 0, 0, gScenarioBufferData13_CLZ_16S, 32, gScenarioKernelData13_CLZ_16S, 4},
{30, 1, 180, 0, 0, gScenarioBufferData14_CLZ_16S, 32, gScenarioKernelData14_CLZ_16S, 4},
{32, 1, 192, 0, 0, gScenarioBufferData15_CLZ_16S, 32, gScenarioKernelData15_CLZ_16S, 4},
{36, 1, 216, 0, 0, gScenarioBufferData16_CLZ_16S, 32, gScenarioKernelData16_CLZ_16S, 4},
{40, 1, 240, 0, 0, gScenarioBufferData17_CLZ_16S, 32, gScenarioKernelData17_CLZ_16S, 4},
{44, 1, 264, 0, 0, gScenarioBufferData18_CLZ_16S, 32, gScenarioKernelData18_CLZ_16S, 4},
{48, 1, 288, 0, 0, gScenarioBufferData19_CLZ_16S, 32, gScenarioKernelData19_CLZ_16S, 4},
{52, 1, 312, 0, 0, gScenarioBufferData20_CLZ_16S, 32, gScenarioKernelData20_CLZ_16S, 4},
{56, 1, 336, 0, 0, gScenarioBufferData21_CLZ_16S, 32, gScenarioKernelData21_CLZ_16S, 4},
{60, 1, 360, 0, 0, gScenarioBufferData22_CLZ_16S, 32, gScenarioKernelData22_CLZ_16S, 4},
{64, 1, 384, 0, 0, gScenarioBufferData23_CLZ_16S, 32, gScenarioKernelData23_CLZ_16S, 4},
{2, 2, 24, 0, 0, gScenarioBufferData24_CLZ_16S, 32, gScenarioKernelData24_CLZ_16S, 4},
{4, 2, 48, 0, 0, gScenarioBufferData25_CLZ_16S, 32, gScenarioKernelData25_CLZ_16S, 4},
{6, 2, 72, 0, 0, gScenarioBufferData26_CLZ_16S, 32, gScenarioKernelData26_CLZ_16S, 4},
{8, 2, 96, 0, 0, gScenarioBufferData27_CLZ_16S, 32, gScenarioKernelData27_CLZ_16S, 4},
{10, 2, 120, 0, 0, gScenarioBufferData28_CLZ_16S, 32, gScenarioKernelData28_CLZ_16S, 4},
{12, 2, 144, 0, 0, gScenarioBufferData29_CLZ_16S, 32, gScenarioKernelData29_CLZ_16S, 4},
{14, 2, 168, 0, 0, gScenarioBufferData30_CLZ_16S, 32, gScenarioKernelData30_CLZ_16S, 4},
{16, 2, 192, 0, 0, gScenarioBufferData31_CLZ_16S, 32, gScenarioKernelData31_CLZ_16S, 4},
{18, 2, 216, 0, 0, gScenarioBufferData32_CLZ_16S, 32, gScenarioKernelData32_CLZ_16S, 4},
{20, 2, 240, 0, 0, gScenarioBufferData33_CLZ_16S, 32, gScenarioKernelData33_CLZ_16S, 4},
{22, 2, 264, 0, 0, gScenarioBufferData34_CLZ_16S, 32, gScenarioKernelData34_CLZ_16S, 4},
{24, 2, 288, 0, 0, gScenarioBufferData35_CLZ_16S, 32, gScenarioKernelData35_CLZ_16S, 4},
{26, 2, 312, 0, 0, gScenarioBufferData36_CLZ_16S, 32, gScenarioKernelData36_CLZ_16S, 4},
{28, 2, 336, 0, 0, gScenarioBufferData37_CLZ_16S, 32, gScenarioKernelData37_CLZ_16S, 4},
{30, 2, 360, 0, 0, gScenarioBufferData38_CLZ_16S, 32, gScenarioKernelData38_CLZ_16S, 4},
{32, 2, 384, 0, 0, gScenarioBufferData39_CLZ_16S, 32, gScenarioKernelData39_CLZ_16S, 4},
{36, 2, 432, 0, 0, gScenarioBufferData40_CLZ_16S, 32, gScenarioKernelData40_CLZ_16S, 4},
{40, 2, 480, 0, 0, gScenarioBufferData41_CLZ_16S, 32, gScenarioKernelData41_CLZ_16S, 4},
{44, 2, 528, 0, 0, gScenarioBufferData42_CLZ_16S, 32, gScenarioKernelData42_CLZ_16S, 4},
{48, 2, 576, 0, 0, gScenarioBufferData43_CLZ_16S, 32, gScenarioKernelData43_CLZ_16S, 4},
{52, 2, 624, 0, 0, gScenarioBufferData44_CLZ_16S, 32, gScenarioKernelData44_CLZ_16S, 4},
{56, 2, 672, 0, 0, gScenarioBufferData45_CLZ_16S, 32, gScenarioKernelData45_CLZ_16S, 4},
{60, 2, 720, 0, 0, gScenarioBufferData46_CLZ_16S, 32, gScenarioKernelData46_CLZ_16S, 4},
{64, 2, 768, 0, 0, gScenarioBufferData47_CLZ_16S, 32, gScenarioKernelData47_CLZ_16S, 4},
{2, 3, 36, 0, 0, gScenarioBufferData48_CLZ_16S, 32, gScenarioKernelData48_CLZ_16S, 4},
{4, 3, 72, 0, 0, gScenarioBufferData49_CLZ_16S, 32, gScenarioKernelData49_CLZ_16S, 4},
{6, 3, 108, 0, 0, gScenarioBufferData50_CLZ_16S, 32, gScenarioKernelData50_CLZ_16S, 4},
{8, 3, 144, 0, 0, gScenarioBufferData51_CLZ_16S, 32, gScenarioKernelData51_CLZ_16S, 4},
{10, 3, 180, 0, 0, gScenarioBufferData52_CLZ_16S, 32, gScenarioKernelData52_CLZ_16S, 4},
{12, 3, 216, 0, 0, gScenarioBufferData53_CLZ_16S, 32, gScenarioKernelData53_CLZ_16S, 4},
{14, 3, 252, 0, 0, gScenarioBufferData54_CLZ_16S, 32, gScenarioKernelData54_CLZ_16S, 4},
{16, 3, 288, 0, 0, gScenarioBufferData55_CLZ_16S, 32, gScenarioKernelData55_CLZ_16S, 4},
{18, 3, 324, 0, 0, gScenarioBufferData56_CLZ_16S, 32, gScenarioKernelData56_CLZ_16S, 4},
{20, 3, 360, 0, 0, gScenarioBufferData57_CLZ_16S, 32, gScenarioKernelData57_CLZ_16S, 4},
{22, 3, 396, 0, 0, gScenarioBufferData58_CLZ_16S, 32, gScenarioKernelData58_CLZ_16S, 4},
{24, 3, 432, 0, 0, gScenarioBufferData59_CLZ_16S, 32, gScenarioKernelData59_CLZ_16S, 4},
{26, 3, 468, 0, 0, gScenarioBufferData60_CLZ_16S, 32, gScenarioKernelData60_CLZ_16S, 4},
{28, 3, 504, 0, 0, gScenarioBufferData61_CLZ_16S, 32, gScenarioKernelData61_CLZ_16S, 4},
{30, 3, 540, 0, 0, gScenarioBufferData62_CLZ_16S, 32, gScenarioKernelData62_CLZ_16S, 4},
{32, 3, 576, 0, 0, gScenarioBufferData63_CLZ_16S, 32, gScenarioKernelData63_CLZ_16S, 4},
{36, 3, 648, 0, 0, gScenarioBufferData64_CLZ_16S, 32, gScenarioKernelData64_CLZ_16S, 4},
{40, 3, 720, 0, 0, gScenarioBufferData65_CLZ_16S, 32, gScenarioKernelData65_CLZ_16S, 4},
{44, 3, 792, 0, 0, gScenarioBufferData66_CLZ_16S, 32, gScenarioKernelData66_CLZ_16S, 4},
{48, 3, 864, 0, 0, gScenarioBufferData67_CLZ_16S, 32, gScenarioKernelData67_CLZ_16S, 4},
{52, 3, 936, 0, 0, gScenarioBufferData68_CLZ_16S, 32, gScenarioKernelData68_CLZ_16S, 4},
{56, 3, 1008, 0, 0, gScenarioBufferData69_CLZ_16S, 32, gScenarioKernelData69_CLZ_16S, 4},
{60, 3, 1080, 0, 0, gScenarioBufferData70_CLZ_16S, 32, gScenarioKernelData70_CLZ_16S, 4},
{64, 3, 1152, 0, 0, gScenarioBufferData71_CLZ_16S, 32, gScenarioKernelData71_CLZ_16S, 4},
{2, 4, 48, 0, 0, gScenarioBufferData72_CLZ_16S, 32, gScenarioKernelData72_CLZ_16S, 4},
{4, 4, 96, 0, 0, gScenarioBufferData73_CLZ_16S, 32, gScenarioKernelData73_CLZ_16S, 4},
{6, 4, 144, 0, 0, gScenarioBufferData74_CLZ_16S, 32, gScenarioKernelData74_CLZ_16S, 4},
{8, 4, 192, 0, 0, gScenarioBufferData75_CLZ_16S, 32, gScenarioKernelData75_CLZ_16S, 4},
{10, 4, 240, 0, 0, gScenarioBufferData76_CLZ_16S, 32, gScenarioKernelData76_CLZ_16S, 4},
{12, 4, 288, 0, 0, gScenarioBufferData77_CLZ_16S, 32, gScenarioKernelData77_CLZ_16S, 4},
{14, 4, 336, 0, 0, gScenarioBufferData78_CLZ_16S, 32, gScenarioKernelData78_CLZ_16S, 4},
{16, 4, 384, 0, 0, gScenarioBufferData79_CLZ_16S, 32, gScenarioKernelData79_CLZ_16S, 4},
{18, 4, 432, 0, 0, gScenarioBufferData80_CLZ_16S, 32, gScenarioKernelData80_CLZ_16S, 4},
{20, 4, 480, 0, 0, gScenarioBufferData81_CLZ_16S, 32, gScenarioKernelData81_CLZ_16S, 4},
{22, 4, 528, 0, 0, gScenarioBufferData82_CLZ_16S, 32, gScenarioKernelData82_CLZ_16S, 4},
{24, 4, 576, 0, 0, gScenarioBufferData83_CLZ_16S, 32, gScenarioKernelData83_CLZ_16S, 4},
{26, 4, 624, 0, 0, gScenarioBufferData84_CLZ_16S, 32, gScenarioKernelData84_CLZ_16S, 4},
{28, 4, 672, 0, 0, gScenarioBufferData85_CLZ_16S, 32, gScenarioKernelData85_CLZ_16S, 4},
{30, 4, 720, 0, 0, gScenarioBufferData86_CLZ_16S, 32, gScenarioKernelData86_CLZ_16S, 4},
{32, 4, 768, 0, 0, gScenarioBufferData87_CLZ_16S, 32, gScenarioKernelData87_CLZ_16S, 4},
{36, 4, 864, 0, 0, gScenarioBufferData88_CLZ_16S, 32, gScenarioKernelData88_CLZ_16S, 4},
{40, 4, 960, 0, 0, gScenarioBufferData89_CLZ_16S, 32, gScenarioKernelData89_CLZ_16S, 4},
{44, 4, 1056, 0, 0, gScenarioBufferData90_CLZ_16S, 32, gScenarioKernelData90_CLZ_16S, 4},
{48, 4, 1152, 0, 0, gScenarioBufferData91_CLZ_16S, 32, gScenarioKernelData91_CLZ_16S, 4},
{52, 4, 1248, 0, 0, gScenarioBufferData92_CLZ_16S, 32, gScenarioKernelData92_CLZ_16S, 4},
{56, 4, 1344, 0, 0, gScenarioBufferData93_CLZ_16S, 32, gScenarioKernelData93_CLZ_16S, 4},
{60, 4, 1440, 0, 0, gScenarioBufferData94_CLZ_16S, 32, gScenarioKernelData94_CLZ_16S, 4},
{64, 4, 1536, 0, 0, gScenarioBufferData95_CLZ_16S, 32, gScenarioKernelData95_CLZ_16S, 4},
{2, 5, 60, 0, 0, gScenarioBufferData96_CLZ_16S, 32, gScenarioKernelData96_CLZ_16S, 4},
{4, 5, 120, 0, 0, gScenarioBufferData97_CLZ_16S, 32, gScenarioKernelData97_CLZ_16S, 4},
{6, 5, 180, 0, 0, gScenarioBufferData98_CLZ_16S, 32, gScenarioKernelData98_CLZ_16S, 4},
{8, 5, 240, 0, 0, gScenarioBufferData99_CLZ_16S, 32, gScenarioKernelData99_CLZ_16S, 4},
{10, 5, 300, 0, 0, gScenarioBufferData100_CLZ_16S, 32, gScenarioKernelData100_CLZ_16S, 4},
{12, 5, 360, 0, 0, gScenarioBufferData101_CLZ_16S, 32, gScenarioKernelData101_CLZ_16S, 4},
{14, 5, 420, 0, 0, gScenarioBufferData102_CLZ_16S, 32, gScenarioKernelData102_CLZ_16S, 4},
{16, 5, 480, 0, 0, gScenarioBufferData103_CLZ_16S, 32, gScenarioKernelData103_CLZ_16S, 4},
{18, 5, 540, 0, 0, gScenarioBufferData104_CLZ_16S, 32, gScenarioKernelData104_CLZ_16S, 4},
{20, 5, 600, 0, 0, gScenarioBufferData105_CLZ_16S, 32, gScenarioKernelData105_CLZ_16S, 4},
{22, 5, 660, 0, 0, gScenarioBufferData106_CLZ_16S, 32, gScenarioKernelData106_CLZ_16S, 4},
{24, 5, 720, 0, 0, gScenarioBufferData107_CLZ_16S, 32, gScenarioKernelData107_CLZ_16S, 4},
{26, 5, 780, 0, 0, gScenarioBufferData108_CLZ_16S, 32, gScenarioKernelData108_CLZ_16S, 4},
{28, 5, 840, 0, 0, gScenarioBufferData109_CLZ_16S, 32, gScenarioKernelData109_CLZ_16S, 4},
{30, 5, 900, 0, 0, gScenarioBufferData110_CLZ_16S, 32, gScenarioKernelData110_CLZ_16S, 4},
{32, 5, 960, 0, 0, gScenarioBufferData111_CLZ_16S, 32, gScenarioKernelData111_CLZ_16S, 4},
{36, 5, 1080, 0, 0, gScenarioBufferData112_CLZ_16S, 32, gScenarioKernelData112_CLZ_16S, 4},
{40, 5, 1200, 0, 0, gScenarioBufferData113_CLZ_16S, 32, gScenarioKernelData113_CLZ_16S, 4},
{44, 5, 1320, 0, 0, gScenarioBufferData114_CLZ_16S, 32, gScenarioKernelData114_CLZ_16S, 4},
{48, 5, 1440, 0, 0, gScenarioBufferData115_CLZ_16S, 32, gScenarioKernelData115_CLZ_16S, 4},
{52, 5, 1560, 0, 0, gScenarioBufferData116_CLZ_16S, 32, gScenarioKernelData116_CLZ_16S, 4},
{56, 5, 1680, 0, 0, gScenarioBufferData117_CLZ_16S, 32, gScenarioKernelData117_CLZ_16S, 4},
{60, 5, 1800, 0, 0, gScenarioBufferData118_CLZ_16S, 32, gScenarioKernelData118_CLZ_16S, 4},
{64, 5, 1920, 0, 0, gScenarioBufferData119_CLZ_16S, 32, gScenarioKernelData119_CLZ_16S, 4},
{2, 6, 72, 0, 0, gScenarioBufferData120_CLZ_16S, 32, gScenarioKernelData120_CLZ_16S, 4},
{4, 6, 144, 0, 0, gScenarioBufferData121_CLZ_16S, 32, gScenarioKernelData121_CLZ_16S, 4},
{6, 6, 216, 0, 0, gScenarioBufferData122_CLZ_16S, 32, gScenarioKernelData122_CLZ_16S, 4},
{8, 6, 288, 0, 0, gScenarioBufferData123_CLZ_16S, 32, gScenarioKernelData123_CLZ_16S, 4},
{10, 6, 360, 0, 0, gScenarioBufferData124_CLZ_16S, 32, gScenarioKernelData124_CLZ_16S, 4},
{12, 6, 432, 0, 0, gScenarioBufferData125_CLZ_16S, 32, gScenarioKernelData125_CLZ_16S, 4},
{14, 6, 504, 0, 0, gScenarioBufferData126_CLZ_16S, 32, gScenarioKernelData126_CLZ_16S, 4},
{16, 6, 576, 0, 0, gScenarioBufferData127_CLZ_16S, 32, gScenarioKernelData127_CLZ_16S, 4},
{18, 6, 648, 0, 0, gScenarioBufferData128_CLZ_16S, 32, gScenarioKernelData128_CLZ_16S, 4},
{20, 6, 720, 0, 0, gScenarioBufferData129_CLZ_16S, 32, gScenarioKernelData129_CLZ_16S, 4},
{22, 6, 792, 0, 0, gScenarioBufferData130_CLZ_16S, 32, gScenarioKernelData130_CLZ_16S, 4},
{24, 6, 864, 0, 0, gScenarioBufferData131_CLZ_16S, 32, gScenarioKernelData131_CLZ_16S, 4},
{26, 6, 936, 0, 0, gScenarioBufferData132_CLZ_16S, 32, gScenarioKernelData132_CLZ_16S, 4},
{28, 6, 1008, 0, 0, gScenarioBufferData133_CLZ_16S, 32, gScenarioKernelData133_CLZ_16S, 4},
{30, 6, 1080, 0, 0, gScenarioBufferData134_CLZ_16S, 32, gScenarioKernelData134_CLZ_16S, 4},
{32, 6, 1152, 0, 0, gScenarioBufferData135_CLZ_16S, 32, gScenarioKernelData135_CLZ_16S, 4},
{36, 6, 1296, 0, 0, gScenarioBufferData136_CLZ_16S, 32, gScenarioKernelData136_CLZ_16S, 4},
{40, 6, 1440, 0, 0, gScenarioBufferData137_CLZ_16S, 32, gScenarioKernelData137_CLZ_16S, 4},
{44, 6, 1584, 0, 0, gScenarioBufferData138_CLZ_16S, 32, gScenarioKernelData138_CLZ_16S, 4},
{48, 6, 1728, 0, 0, gScenarioBufferData139_CLZ_16S, 32, gScenarioKernelData139_CLZ_16S, 4},
{52, 6, 1872, 0, 0, gScenarioBufferData140_CLZ_16S, 32, gScenarioKernelData140_CLZ_16S, 4},
{56, 6, 2016, 0, 0, gScenarioBufferData141_CLZ_16S, 32, gScenarioKernelData141_CLZ_16S, 4},
{60, 6, 2160, 0, 0, gScenarioBufferData142_CLZ_16S, 32, gScenarioKernelData142_CLZ_16S, 4},
{64, 6, 2304, 0, 0, gScenarioBufferData143_CLZ_16S, 32, gScenarioKernelData143_CLZ_16S, 4},
{2, 8, 96, 0, 0, gScenarioBufferData144_CLZ_16S, 32, gScenarioKernelData144_CLZ_16S, 4},
{4, 8, 192, 0, 0, gScenarioBufferData145_CLZ_16S, 32, gScenarioKernelData145_CLZ_16S, 4},
{6, 8, 288, 0, 0, gScenarioBufferData146_CLZ_16S, 32, gScenarioKernelData146_CLZ_16S, 4},
{8, 8, 384, 0, 0, gScenarioBufferData147_CLZ_16S, 32, gScenarioKernelData147_CLZ_16S, 4},
{10, 8, 480, 0, 0, gScenarioBufferData148_CLZ_16S, 32, gScenarioKernelData148_CLZ_16S, 4},
{12, 8, 576, 0, 0, gScenarioBufferData149_CLZ_16S, 32, gScenarioKernelData149_CLZ_16S, 4},
{14, 8, 672, 0, 0, gScenarioBufferData150_CLZ_16S, 32, gScenarioKernelData150_CLZ_16S, 4},
{16, 8, 768, 0, 0, gScenarioBufferData151_CLZ_16S, 32, gScenarioKernelData151_CLZ_16S, 4},
{18, 8, 864, 0, 0, gScenarioBufferData152_CLZ_16S, 32, gScenarioKernelData152_CLZ_16S, 4},
{20, 8, 960, 0, 0, gScenarioBufferData153_CLZ_16S, 32, gScenarioKernelData153_CLZ_16S, 4},
{22, 8, 1056, 0, 0, gScenarioBufferData154_CLZ_16S, 32, gScenarioKernelData154_CLZ_16S, 4},
{24, 8, 1152, 0, 0, gScenarioBufferData155_CLZ_16S, 32, gScenarioKernelData155_CLZ_16S, 4},
{26, 8, 1248, 0, 0, gScenarioBufferData156_CLZ_16S, 32, gScenarioKernelData156_CLZ_16S, 4},
{28, 8, 1344, 0, 0, gScenarioBufferData157_CLZ_16S, 32, gScenarioKernelData157_CLZ_16S, 4},
{30, 8, 1440, 0, 0, gScenarioBufferData158_CLZ_16S, 32, gScenarioKernelData158_CLZ_16S, 4},
{32, 8, 1536, 0, 0, gScenarioBufferData159_CLZ_16S, 32, gScenarioKernelData159_CLZ_16S, 4},
{36, 8, 1728, 0, 0, gScenarioBufferData160_CLZ_16S, 32, gScenarioKernelData160_CLZ_16S, 4},
{40, 8, 1920, 0, 0, gScenarioBufferData161_CLZ_16S, 32, gScenarioKernelData161_CLZ_16S, 4},
{44, 8, 2112, 0, 0, gScenarioBufferData162_CLZ_16S, 32, gScenarioKernelData162_CLZ_16S, 4},
{48, 8, 2304, 0, 0, gScenarioBufferData163_CLZ_16S, 32, gScenarioKernelData163_CLZ_16S, 4},
{52, 8, 2496, 0, 0, gScenarioBufferData164_CLZ_16S, 32, gScenarioKernelData164_CLZ_16S, 4},
{56, 8, 2688, 0, 0, gScenarioBufferData165_CLZ_16S, 32, gScenarioKernelData165_CLZ_16S, 4},
{60, 8, 2880, 0, 0, gScenarioBufferData166_CLZ_16S, 32, gScenarioKernelData166_CLZ_16S, 4},
{64, 8, 3072, 0, 0, gScenarioBufferData167_CLZ_16S, 32, gScenarioKernelData167_CLZ_16S, 4},
{2, 10, 120, 0, 0, gScenarioBufferData168_CLZ_16S, 32, gScenarioKernelData168_CLZ_16S, 4},
{4, 10, 240, 0, 0, gScenarioBufferData169_CLZ_16S, 32, gScenarioKernelData169_CLZ_16S, 4},
{6, 10, 360, 0, 0, gScenarioBufferData170_CLZ_16S, 32, gScenarioKernelData170_CLZ_16S, 4},
{8, 10, 480, 0, 0, gScenarioBufferData171_CLZ_16S, 32, gScenarioKernelData171_CLZ_16S, 4},
{10, 10, 600, 0, 0, gScenarioBufferData172_CLZ_16S, 32, gScenarioKernelData172_CLZ_16S, 4},
{12, 10, 720, 0, 0, gScenarioBufferData173_CLZ_16S, 32, gScenarioKernelData173_CLZ_16S, 4},
{14, 10, 840, 0, 0, gScenarioBufferData174_CLZ_16S, 32, gScenarioKernelData174_CLZ_16S, 4},
{16, 10, 960, 0, 0, gScenarioBufferData175_CLZ_16S, 32, gScenarioKernelData175_CLZ_16S, 4},
{18, 10, 1080, 0, 0, gScenarioBufferData176_CLZ_16S, 32, gScenarioKernelData176_CLZ_16S, 4},
{20, 10, 1200, 0, 0, gScenarioBufferData177_CLZ_16S, 32, gScenarioKernelData177_CLZ_16S, 4},
{22, 10, 1320, 0, 0, gScenarioBufferData178_CLZ_16S, 32, gScenarioKernelData178_CLZ_16S, 4},
{24, 10, 1440, 0, 0, gScenarioBufferData179_CLZ_16S, 32, gScenarioKernelData179_CLZ_16S, 4},
{26, 10, 1560, 0, 0, gScenarioBufferData180_CLZ_16S, 32, gScenarioKernelData180_CLZ_16S, 4},
{28, 10, 1680, 0, 0, gScenarioBufferData181_CLZ_16S, 32, gScenarioKernelData181_CLZ_16S, 4},
{30, 10, 1800, 0, 0, gScenarioBufferData182_CLZ_16S, 32, gScenarioKernelData182_CLZ_16S, 4},
{32, 10, 1920, 0, 0, gScenarioBufferData183_CLZ_16S, 32, gScenarioKernelData183_CLZ_16S, 4},
{36, 10, 2160, 0, 0, gScenarioBufferData184_CLZ_16S, 32, gScenarioKernelData184_CLZ_16S, 4},
{40, 10, 2400, 0, 0, gScenarioBufferData185_CLZ_16S, 32, gScenarioKernelData185_CLZ_16S, 4},
{44, 10, 2640, 0, 0, gScenarioBufferData186_CLZ_16S, 32, gScenarioKernelData186_CLZ_16S, 4},
{48, 10, 2880, 0, 0, gScenarioBufferData187_CLZ_16S, 32, gScenarioKernelData187_CLZ_16S, 4},
{52, 10, 3120, 0, 0, gScenarioBufferData188_CLZ_16S, 32, gScenarioKernelData188_CLZ_16S, 4},
{56, 10, 3360, 0, 0, gScenarioBufferData189_CLZ_16S, 32, gScenarioKernelData189_CLZ_16S, 4},
{60, 10, 3600, 0, 0, gScenarioBufferData190_CLZ_16S, 32, gScenarioKernelData190_CLZ_16S, 4},
{64, 10, 3840, 0, 0, gScenarioBufferData191_CLZ_16S, 32, gScenarioKernelData191_CLZ_16S, 4},
{2, 12, 144, 0, 0, gScenarioBufferData192_CLZ_16S, 32, gScenarioKernelData192_CLZ_16S, 4},
{4, 12, 288, 0, 0, gScenarioBufferData193_CLZ_16S, 32, gScenarioKernelData193_CLZ_16S, 4},
{6, 12, 432, 0, 0, gScenarioBufferData194_CLZ_16S, 32, gScenarioKernelData194_CLZ_16S, 4},
{8, 12, 576, 0, 0, gScenarioBufferData195_CLZ_16S, 32, gScenarioKernelData195_CLZ_16S, 4},
{10, 12, 720, 0, 0, gScenarioBufferData196_CLZ_16S, 32, gScenarioKernelData196_CLZ_16S, 4},
{12, 12, 864, 0, 0, gScenarioBufferData197_CLZ_16S, 32, gScenarioKernelData197_CLZ_16S, 4},
{14, 12, 1008, 0, 0, gScenarioBufferData198_CLZ_16S, 32, gScenarioKernelData198_CLZ_16S, 4},
{16, 12, 1152, 0, 0, gScenarioBufferData199_CLZ_16S, 32, gScenarioKernelData199_CLZ_16S, 4},
{18, 12, 1296, 0, 0, gScenarioBufferData200_CLZ_16S, 32, gScenarioKernelData200_CLZ_16S, 4},
{20, 12, 1440, 0, 0, gScenarioBufferData201_CLZ_16S, 32, gScenarioKernelData201_CLZ_16S, 4},
{22, 12, 1584, 0, 0, gScenarioBufferData202_CLZ_16S, 32, gScenarioKernelData202_CLZ_16S, 4},
{24, 12, 1728, 0, 0, gScenarioBufferData203_CLZ_16S, 32, gScenarioKernelData203_CLZ_16S, 4},
{26, 12, 1872, 0, 0, gScenarioBufferData204_CLZ_16S, 32, gScenarioKernelData204_CLZ_16S, 4},
{28, 12, 2016, 0, 0, gScenarioBufferData205_CLZ_16S, 32, gScenarioKernelData205_CLZ_16S, 4},
{30, 12, 2160, 0, 0, gScenarioBufferData206_CLZ_16S, 32, gScenarioKernelData206_CLZ_16S, 4},
{32, 12, 2304, 0, 0, gScenarioBufferData207_CLZ_16S, 32, gScenarioKernelData207_CLZ_16S, 4},
{36, 12, 2592, 0, 0, gScenarioBufferData208_CLZ_16S, 32, gScenarioKernelData208_CLZ_16S, 4},
{40, 12, 2880, 0, 0, gScenarioBufferData209_CLZ_16S, 32, gScenarioKernelData209_CLZ_16S, 4},
{44, 12, 3168, 0, 0, gScenarioBufferData210_CLZ_16S, 32, gScenarioKernelData210_CLZ_16S, 4},
{48, 12, 3456, 0, 0, gScenarioBufferData211_CLZ_16S, 32, gScenarioKernelData211_CLZ_16S, 4},
{52, 12, 3744, 0, 0, gScenarioBufferData212_CLZ_16S, 32, gScenarioKernelData212_CLZ_16S, 4},
{2, 14, 168, 0, 0, gScenarioBufferData213_CLZ_16S, 32, gScenarioKernelData213_CLZ_16S, 4},
{4, 14, 336, 0, 0, gScenarioBufferData214_CLZ_16S, 32, gScenarioKernelData214_CLZ_16S, 4},
{6, 14, 504, 0, 0, gScenarioBufferData215_CLZ_16S, 32, gScenarioKernelData215_CLZ_16S, 4},
{8, 14, 672, 0, 0, gScenarioBufferData216_CLZ_16S, 32, gScenarioKernelData216_CLZ_16S, 4},
{10, 14, 840, 0, 0, gScenarioBufferData217_CLZ_16S, 32, gScenarioKernelData217_CLZ_16S, 4},
{12, 14, 1008, 0, 0, gScenarioBufferData218_CLZ_16S, 32, gScenarioKernelData218_CLZ_16S, 4},
{14, 14, 1176, 0, 0, gScenarioBufferData219_CLZ_16S, 32, gScenarioKernelData219_CLZ_16S, 4},
{16, 14, 1344, 0, 0, gScenarioBufferData220_CLZ_16S, 32, gScenarioKernelData220_CLZ_16S, 4},
{18, 14, 1512, 0, 0, gScenarioBufferData221_CLZ_16S, 32, gScenarioKernelData221_CLZ_16S, 4},
{20, 14, 1680, 0, 0, gScenarioBufferData222_CLZ_16S, 32, gScenarioKernelData222_CLZ_16S, 4},
{22, 14, 1848, 0, 0, gScenarioBufferData223_CLZ_16S, 32, gScenarioKernelData223_CLZ_16S, 4},
{24, 14, 2016, 0, 0, gScenarioBufferData224_CLZ_16S, 32, gScenarioKernelData224_CLZ_16S, 4},
{26, 14, 2184, 0, 0, gScenarioBufferData225_CLZ_16S, 32, gScenarioKernelData225_CLZ_16S, 4},
{28, 14, 2352, 0, 0, gScenarioBufferData226_CLZ_16S, 32, gScenarioKernelData226_CLZ_16S, 4},
{30, 14, 2520, 0, 0, gScenarioBufferData227_CLZ_16S, 32, gScenarioKernelData227_CLZ_16S, 4},
{32, 14, 2688, 0, 0, gScenarioBufferData228_CLZ_16S, 32, gScenarioKernelData228_CLZ_16S, 4},
{36, 14, 3024, 0, 0, gScenarioBufferData229_CLZ_16S, 32, gScenarioKernelData229_CLZ_16S, 4},
{40, 14, 3360, 0, 0, gScenarioBufferData230_CLZ_16S, 32, gScenarioKernelData230_CLZ_16S, 4},
{44, 14, 3696, 0, 0, gScenarioBufferData231_CLZ_16S, 32, gScenarioKernelData231_CLZ_16S, 4},
{2, 16, 192, 0, 0, gScenarioBufferData232_CLZ_16S, 32, gScenarioKernelData232_CLZ_16S, 4},
{4, 16, 384, 0, 0, gScenarioBufferData233_CLZ_16S, 32, gScenarioKernelData233_CLZ_16S, 4},
{6, 16, 576, 0, 0, gScenarioBufferData234_CLZ_16S, 32, gScenarioKernelData234_CLZ_16S, 4},
{8, 16, 768, 0, 0, gScenarioBufferData235_CLZ_16S, 32, gScenarioKernelData235_CLZ_16S, 4},
{10, 16, 960, 0, 0, gScenarioBufferData236_CLZ_16S, 32, gScenarioKernelData236_CLZ_16S, 4},
{12, 16, 1152, 0, 0, gScenarioBufferData237_CLZ_16S, 32, gScenarioKernelData237_CLZ_16S, 4},
{14, 16, 1344, 0, 0, gScenarioBufferData238_CLZ_16S, 32, gScenarioKernelData238_CLZ_16S, 4},
{16, 16, 1536, 0, 0, gScenarioBufferData239_CLZ_16S, 32, gScenarioKernelData239_CLZ_16S, 4},
{18, 16, 1728, 0, 0, gScenarioBufferData240_CLZ_16S, 32, gScenarioKernelData240_CLZ_16S, 4},
{20, 16, 1920, 0, 0, gScenarioBufferData241_CLZ_16S, 32, gScenarioKernelData241_CLZ_16S, 4},
{22, 16, 2112, 0, 0, gScenarioBufferData242_CLZ_16S, 32, gScenarioKernelData242_CLZ_16S, 4},
{24, 16, 2304, 0, 0, gScenarioBufferData243_CLZ_16S, 32, gScenarioKernelData243_CLZ_16S, 4},
{26, 16, 2496, 0, 0, gScenarioBufferData244_CLZ_16S, 32, gScenarioKernelData244_CLZ_16S, 4},
{28, 16, 2688, 0, 0, gScenarioBufferData245_CLZ_16S, 32, gScenarioKernelData245_CLZ_16S, 4},
{30, 16, 2880, 0, 0, gScenarioBufferData246_CLZ_16S, 32, gScenarioKernelData246_CLZ_16S, 4},
{32, 16, 3072, 0, 0, gScenarioBufferData247_CLZ_16S, 32, gScenarioKernelData247_CLZ_16S, 4},
{36, 16, 3456, 0, 0, gScenarioBufferData248_CLZ_16S, 32, gScenarioKernelData248_CLZ_16S, 4},
{40, 16, 3840, 0, 0, gScenarioBufferData249_CLZ_16S, 32, gScenarioKernelData249_CLZ_16S, 4},
{2, 18, 216, 0, 0, gScenarioBufferData250_CLZ_16S, 32, gScenarioKernelData250_CLZ_16S, 4},
{4, 18, 432, 0, 0, gScenarioBufferData251_CLZ_16S, 32, gScenarioKernelData251_CLZ_16S, 4},
{6, 18, 648, 0, 0, gScenarioBufferData252_CLZ_16S, 32, gScenarioKernelData252_CLZ_16S, 4},
{8, 18, 864, 0, 0, gScenarioBufferData253_CLZ_16S, 32, gScenarioKernelData253_CLZ_16S, 4},
{10, 18, 1080, 0, 0, gScenarioBufferData254_CLZ_16S, 32, gScenarioKernelData254_CLZ_16S, 4},
{12, 18, 1296, 0, 0, gScenarioBufferData255_CLZ_16S, 32, gScenarioKernelData255_CLZ_16S, 4},
{14, 18, 1512, 0, 0, gScenarioBufferData256_CLZ_16S, 32, gScenarioKernelData256_CLZ_16S, 4},
{16, 18, 1728, 0, 0, gScenarioBufferData257_CLZ_16S, 32, gScenarioKernelData257_CLZ_16S, 4},
{18, 18, 1944, 0, 0, gScenarioBufferData258_CLZ_16S, 32, gScenarioKernelData258_CLZ_16S, 4},
{20, 18, 2160, 0, 0, gScenarioBufferData259_CLZ_16S, 32, gScenarioKernelData259_CLZ_16S, 4},
{22, 18, 2376, 0, 0, gScenarioBufferData260_CLZ_16S, 32, gScenarioKernelData260_CLZ_16S, 4},
{24, 18, 2592, 0, 0, gScenarioBufferData261_CLZ_16S, 32, gScenarioKernelData261_CLZ_16S, 4},
{26, 18, 2808, 0, 0, gScenarioBufferData262_CLZ_16S, 32, gScenarioKernelData262_CLZ_16S, 4},
{28, 18, 3024, 0, 0, gScenarioBufferData263_CLZ_16S, 32, gScenarioKernelData263_CLZ_16S, 4},
{30, 18, 3240, 0, 0, gScenarioBufferData264_CLZ_16S, 32, gScenarioKernelData264_CLZ_16S, 4},
{32, 18, 3456, 0, 0, gScenarioBufferData265_CLZ_16S, 32, gScenarioKernelData265_CLZ_16S, 4},
{2, 20, 240, 0, 0, gScenarioBufferData266_CLZ_16S, 32, gScenarioKernelData266_CLZ_16S, 4},
{4, 20, 480, 0, 0, gScenarioBufferData267_CLZ_16S, 32, gScenarioKernelData267_CLZ_16S, 4},
{6, 20, 720, 0, 0, gScenarioBufferData268_CLZ_16S, 32, gScenarioKernelData268_CLZ_16S, 4},
{8, 20, 960, 0, 0, gScenarioBufferData269_CLZ_16S, 32, gScenarioKernelData269_CLZ_16S, 4},
{10, 20, 1200, 0, 0, gScenarioBufferData270_CLZ_16S, 32, gScenarioKernelData270_CLZ_16S, 4},
{12, 20, 1440, 0, 0, gScenarioBufferData271_CLZ_16S, 32, gScenarioKernelData271_CLZ_16S, 4},
{14, 20, 1680, 0, 0, gScenarioBufferData272_CLZ_16S, 32, gScenarioKernelData272_CLZ_16S, 4},
{16, 20, 1920, 0, 0, gScenarioBufferData273_CLZ_16S, 32, gScenarioKernelData273_CLZ_16S, 4},
{18, 20, 2160, 0, 0, gScenarioBufferData274_CLZ_16S, 32, gScenarioKernelData274_CLZ_16S, 4},
{20, 20, 2400, 0, 0, gScenarioBufferData275_CLZ_16S, 32, gScenarioKernelData275_CLZ_16S, 4},
{22, 20, 2640, 0, 0, gScenarioBufferData276_CLZ_16S, 32, gScenarioKernelData276_CLZ_16S, 4},
{24, 20, 2880, 0, 0, gScenarioBufferData277_CLZ_16S, 32, gScenarioKernelData277_CLZ_16S, 4},
{26, 20, 3120, 0, 0, gScenarioBufferData278_CLZ_16S, 32, gScenarioKernelData278_CLZ_16S, 4},
{28, 20, 3360, 0, 0, gScenarioBufferData279_CLZ_16S, 32, gScenarioKernelData279_CLZ_16S, 4},
{30, 20, 3600, 0, 0, gScenarioBufferData280_CLZ_16S, 32, gScenarioKernelData280_CLZ_16S, 4},
{32, 20, 3840, 0, 0, gScenarioBufferData281_CLZ_16S, 32, gScenarioKernelData281_CLZ_16S, 4},
{2, 22, 264, 0, 0, gScenarioBufferData282_CLZ_16S, 32, gScenarioKernelData282_CLZ_16S, 4},
{4, 22, 528, 0, 0, gScenarioBufferData283_CLZ_16S, 32, gScenarioKernelData283_CLZ_16S, 4},
{6, 22, 792, 0, 0, gScenarioBufferData284_CLZ_16S, 32, gScenarioKernelData284_CLZ_16S, 4},
{8, 22, 1056, 0, 0, gScenarioBufferData285_CLZ_16S, 32, gScenarioKernelData285_CLZ_16S, 4},
{10, 22, 1320, 0, 0, gScenarioBufferData286_CLZ_16S, 32, gScenarioKernelData286_CLZ_16S, 4},
{12, 22, 1584, 0, 0, gScenarioBufferData287_CLZ_16S, 32, gScenarioKernelData287_CLZ_16S, 4},
{14, 22, 1848, 0, 0, gScenarioBufferData288_CLZ_16S, 32, gScenarioKernelData288_CLZ_16S, 4},
{16, 22, 2112, 0, 0, gScenarioBufferData289_CLZ_16S, 32, gScenarioKernelData289_CLZ_16S, 4},
{18, 22, 2376, 0, 0, gScenarioBufferData290_CLZ_16S, 32, gScenarioKernelData290_CLZ_16S, 4},
{20, 22, 2640, 0, 0, gScenarioBufferData291_CLZ_16S, 32, gScenarioKernelData291_CLZ_16S, 4},
{22, 22, 2904, 0, 0, gScenarioBufferData292_CLZ_16S, 32, gScenarioKernelData292_CLZ_16S, 4},
{24, 22, 3168, 0, 0, gScenarioBufferData293_CLZ_16S, 32, gScenarioKernelData293_CLZ_16S, 4},
{26, 22, 3432, 0, 0, gScenarioBufferData294_CLZ_16S, 32, gScenarioKernelData294_CLZ_16S, 4},
{28, 22, 3696, 0, 0, gScenarioBufferData295_CLZ_16S, 32, gScenarioKernelData295_CLZ_16S, 4},
{2, 24, 288, 0, 0, gScenarioBufferData296_CLZ_16S, 32, gScenarioKernelData296_CLZ_16S, 4},
{4, 24, 576, 0, 0, gScenarioBufferData297_CLZ_16S, 32, gScenarioKernelData297_CLZ_16S, 4},
{6, 24, 864, 0, 0, gScenarioBufferData298_CLZ_16S, 32, gScenarioKernelData298_CLZ_16S, 4},
{8, 24, 1152, 0, 0, gScenarioBufferData299_CLZ_16S, 32, gScenarioKernelData299_CLZ_16S, 4},
{10, 24, 1440, 0, 0, gScenarioBufferData300_CLZ_16S, 32, gScenarioKernelData300_CLZ_16S, 4},
{12, 24, 1728, 0, 0, gScenarioBufferData301_CLZ_16S, 32, gScenarioKernelData301_CLZ_16S, 4},
{14, 24, 2016, 0, 0, gScenarioBufferData302_CLZ_16S, 32, gScenarioKernelData302_CLZ_16S, 4},
{16, 24, 2304, 0, 0, gScenarioBufferData303_CLZ_16S, 32, gScenarioKernelData303_CLZ_16S, 4},
{18, 24, 2592, 0, 0, gScenarioBufferData304_CLZ_16S, 32, gScenarioKernelData304_CLZ_16S, 4},
{20, 24, 2880, 0, 0, gScenarioBufferData305_CLZ_16S, 32, gScenarioKernelData305_CLZ_16S, 4},
{22, 24, 3168, 0, 0, gScenarioBufferData306_CLZ_16S, 32, gScenarioKernelData306_CLZ_16S, 4},
{24, 24, 3456, 0, 0, gScenarioBufferData307_CLZ_16S, 32, gScenarioKernelData307_CLZ_16S, 4},
{26, 24, 3744, 0, 0, gScenarioBufferData308_CLZ_16S, 32, gScenarioKernelData308_CLZ_16S, 4},
{2, 26, 312, 0, 0, gScenarioBufferData309_CLZ_16S, 32, gScenarioKernelData309_CLZ_16S, 4},
{4, 26, 624, 0, 0, gScenarioBufferData310_CLZ_16S, 32, gScenarioKernelData310_CLZ_16S, 4},
{6, 26, 936, 0, 0, gScenarioBufferData311_CLZ_16S, 32, gScenarioKernelData311_CLZ_16S, 4},
{8, 26, 1248, 0, 0, gScenarioBufferData312_CLZ_16S, 32, gScenarioKernelData312_CLZ_16S, 4},
{10, 26, 1560, 0, 0, gScenarioBufferData313_CLZ_16S, 32, gScenarioKernelData313_CLZ_16S, 4},
{12, 26, 1872, 0, 0, gScenarioBufferData314_CLZ_16S, 32, gScenarioKernelData314_CLZ_16S, 4},
{14, 26, 2184, 0, 0, gScenarioBufferData315_CLZ_16S, 32, gScenarioKernelData315_CLZ_16S, 4},
{16, 26, 2496, 0, 0, gScenarioBufferData316_CLZ_16S, 32, gScenarioKernelData316_CLZ_16S, 4},
{18, 26, 2808, 0, 0, gScenarioBufferData317_CLZ_16S, 32, gScenarioKernelData317_CLZ_16S, 4},
{20, 26, 3120, 0, 0, gScenarioBufferData318_CLZ_16S, 32, gScenarioKernelData318_CLZ_16S, 4},
{22, 26, 3432, 0, 0, gScenarioBufferData319_CLZ_16S, 32, gScenarioKernelData319_CLZ_16S, 4},
{24, 26, 3744, 0, 0, gScenarioBufferData320_CLZ_16S, 32, gScenarioKernelData320_CLZ_16S, 4},
{2, 28, 336, 0, 0, gScenarioBufferData321_CLZ_16S, 32, gScenarioKernelData321_CLZ_16S, 4},
{4, 28, 672, 0, 0, gScenarioBufferData322_CLZ_16S, 32, gScenarioKernelData322_CLZ_16S, 4},
{6, 28, 1008, 0, 0, gScenarioBufferData323_CLZ_16S, 32, gScenarioKernelData323_CLZ_16S, 4},
{8, 28, 1344, 0, 0, gScenarioBufferData324_CLZ_16S, 32, gScenarioKernelData324_CLZ_16S, 4},
{10, 28, 1680, 0, 0, gScenarioBufferData325_CLZ_16S, 32, gScenarioKernelData325_CLZ_16S, 4},
{12, 28, 2016, 0, 0, gScenarioBufferData326_CLZ_16S, 32, gScenarioKernelData326_CLZ_16S, 4},
{14, 28, 2352, 0, 0, gScenarioBufferData327_CLZ_16S, 32, gScenarioKernelData327_CLZ_16S, 4},
{16, 28, 2688, 0, 0, gScenarioBufferData328_CLZ_16S, 32, gScenarioKernelData328_CLZ_16S, 4},
{18, 28, 3024, 0, 0, gScenarioBufferData329_CLZ_16S, 32, gScenarioKernelData329_CLZ_16S, 4},
{20, 28, 3360, 0, 0, gScenarioBufferData330_CLZ_16S, 32, gScenarioKernelData330_CLZ_16S, 4},
{22, 28, 3696, 0, 0, gScenarioBufferData331_CLZ_16S, 32, gScenarioKernelData331_CLZ_16S, 4},
{2, 30, 360, 0, 0, gScenarioBufferData332_CLZ_16S, 32, gScenarioKernelData332_CLZ_16S, 4},
{4, 30, 720, 0, 0, gScenarioBufferData333_CLZ_16S, 32, gScenarioKernelData333_CLZ_16S, 4},
{6, 30, 1080, 0, 0, gScenarioBufferData334_CLZ_16S, 32, gScenarioKernelData334_CLZ_16S, 4},
{8, 30, 1440, 0, 0, gScenarioBufferData335_CLZ_16S, 32, gScenarioKernelData335_CLZ_16S, 4},
{10, 30, 1800, 0, 0, gScenarioBufferData336_CLZ_16S, 32, gScenarioKernelData336_CLZ_16S, 4},
{12, 30, 2160, 0, 0, gScenarioBufferData337_CLZ_16S, 32, gScenarioKernelData337_CLZ_16S, 4},
{14, 30, 2520, 0, 0, gScenarioBufferData338_CLZ_16S, 32, gScenarioKernelData338_CLZ_16S, 4},
{16, 30, 2880, 0, 0, gScenarioBufferData339_CLZ_16S, 32, gScenarioKernelData339_CLZ_16S, 4},
{18, 30, 3240, 0, 0, gScenarioBufferData340_CLZ_16S, 32, gScenarioKernelData340_CLZ_16S, 4},
{20, 30, 3600, 0, 0, gScenarioBufferData341_CLZ_16S, 32, gScenarioKernelData341_CLZ_16S, 4},
{2, 32, 384, 0, 0, gScenarioBufferData342_CLZ_16S, 32, gScenarioKernelData342_CLZ_16S, 4},
{4, 32, 768, 0, 0, gScenarioBufferData343_CLZ_16S, 32, gScenarioKernelData343_CLZ_16S, 4},
{6, 32, 1152, 0, 0, gScenarioBufferData344_CLZ_16S, 32, gScenarioKernelData344_CLZ_16S, 4},
{8, 32, 1536, 0, 0, gScenarioBufferData345_CLZ_16S, 32, gScenarioKernelData345_CLZ_16S, 4},
{10, 32, 1920, 0, 0, gScenarioBufferData346_CLZ_16S, 32, gScenarioKernelData346_CLZ_16S, 4},
{12, 32, 2304, 0, 0, gScenarioBufferData347_CLZ_16S, 32, gScenarioKernelData347_CLZ_16S, 4},
{14, 32, 2688, 0, 0, gScenarioBufferData348_CLZ_16S, 32, gScenarioKernelData348_CLZ_16S, 4},
{16, 32, 3072, 0, 0, gScenarioBufferData349_CLZ_16S, 32, gScenarioKernelData349_CLZ_16S, 4},
{18, 32, 3456, 0, 0, gScenarioBufferData350_CLZ_16S, 32, gScenarioKernelData350_CLZ_16S, 4},
{20, 32, 3840, 0, 0, gScenarioBufferData351_CLZ_16S, 32, gScenarioKernelData351_CLZ_16S, 4}
};

static acf_scenario_list gScenarioList_CLZ_16S = {
352, //number of scenarios
gScenarioArray_CLZ_16S};
//**************************************************************

class CLZ_16S : public ACF_Process_APU
{

public:
   CLZ_16S(int32_t apex_id = 0) : ACF_Process_APU(apex_id)
   {} 

   int32_t Initialize()
   {
      int32_t lRetVal = 0;

      if (!Initialized()) //initialization steps that only need to occur once
      {
         SetProcessIdentifier("CLZ_16S");

         lRetVal = NonParametricInitialization();
         if (lRetVal != 0) return lRetVal;

         lRetVal |= mpApexTask->SetupHw("CLZ_16S",
                                        CLZ_16S_LOAD_SEGMENTS,
                                        CLZ_16S_LOAD_PMEM, CLZ_16S_LOAD_PMEM_SIZE,
                                        CLZ_16S_LOAD_DMEM, CLZ_16S_LOAD_DMEM_SIZE,
                                        0, 0); //assuming _LOAD_CMEM does not exist
         SetApuStdioInfo(CLZ_16S_APEX_LOG_BUFFER, CLZ_16S_APEX_LOG_SIZE);

         if (lRetVal != 0) return lRetVal;

         //***NOTE: the order in which the following ports are added is meaningful; do not change!

         AddPort("INPUT_0", icp::DATATYPE_16S, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
         AddPort("OUTPUT_0", icp::DATATYPE_08U, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);

         CfgScenarios(&gScenarioList_CLZ_16S);

         FlagAsInitialized();
      }

      lRetVal = SelectApuConfiguration(mApuCfg, mApexId); //by default mApuCfg = ACF_APU_CFG__APEX0_DEFAULT and mApexId = 0

      return lRetVal;
   }
};

#endif //_ACF_PROCESS_APU_CLZ_16S
