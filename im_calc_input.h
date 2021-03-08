//
// Created by bb1950328 on 08.03.2021.
//

#ifndef IMCALCINPUTTESTING_IM_CALC_INPUT_H
#define IMCALCINPUTTESTING_IM_CALC_INPUT_H

#include <imgui.h>

namespace ImCalcInput {
    bool InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
}
#endif //IMCALCINPUTTESTING_IM_CALC_INPUT_H
