//
// Created by bb1950328 on 08.03.2021.
//

#include "im_calc_input.h"
#include <cstdio>
#include <iostream>
#include "IconsFontAwesome5.h"

namespace ImCalcInput {

    bool InputDouble(const char *label, double *v, double step, double step_fast, const char *format, ImGuiInputTextFlags flags) {
        const auto childLabelSize = 11 + strlen(label);
        char childLabel[childLabelSize];
        std::snprintf(childLabel, childLabelSize, "ImCalcInput%s", label);
        if (ImGui::BeginChild(childLabel)) {
            ImGui::InputDouble("", v, step, step_fast, format, flags);
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_CALCULATOR)) {
                std::cout << "TODO open calculator" << std::endl;
            }
            ImGui::SameLine();
            ImGui::Text("%s", label);
            ImGui::EndChild();
            return true;
        }
        return false;
    }
}