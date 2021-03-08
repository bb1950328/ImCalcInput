//
// Created by bb1950328 on 08.03.2021.
//

#include "im_calc_input.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <map>
#include "IconsFontAwesome5.h"

#if IMCALCINPUT_PLATFORM==IMCALCINPUT_GLFW
#include <GLFW/glfw3.h>
#endif


namespace ImCalcInput {

    namespace {
        void OpenCalculator::focusNextTime() {
            isFocusNextTime = true;
        }

        void ImCalcInput::OpenCalculator::draw() {
            bool open = true;
            if (isFocusNextTime) {
                ImGui::SetNextWindowFocus();
                isFocusNextTime = false;
            }
            ImGui::Begin(label, &open, ImGuiWindowFlags_AlwaysAutoResize);
            auto& io = ImGui::GetIO();

            for (const ImWchar &queueChar : io.InputQueueCharacters) {
                if (strchr(INPUT_QUEUE_HANDLED_BUTTONS, queueChar)) {
                    buttonPressed(static_cast<Button>(queueChar));
                }
            }
            io.InputQueueCharacters.resize(0);

            ImGui::Text("%s", currentInputText);

            ImVec2 squareButtonSize = {ImGui::GetStyle().FramePadding.x*2+ImGui::GetFontSize(), ImGui::GetStyle().FramePadding.y*2+ImGui::GetFontSize()};
            ImVec2 landscapeDoubleButtonSize = {squareButtonSize.x*2+ImGui::GetStyle().ItemSpacing.x, squareButtonSize.y};

            drawButton(Button::NUM_7, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_8, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_9, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::PLUS, squareButtonSize);

            drawButton(Button::NUM_4, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_5, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_6, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::MINUS, squareButtonSize);

            drawButton(Button::NUM_1, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_2, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::NUM_3, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::DIVISION, squareButtonSize);

            drawButton(Button::BACKSPACE, squareButtonSize);
            ImGui::SameLine();
            drawButton(Button::ENTER, landscapeDoubleButtonSize);
            ImGui::SameLine();
            drawButton(Button::MULTIPLICATION, squareButtonSize);

            ImGui::End();
        }

        ImCalcInput::OpenCalculator::OpenCalculator(const char *label, const double *valuePtr) : label(label), inputValue(valuePtr), inputValueType(ValueType::DOUBLE) {}
        ImCalcInput::OpenCalculator::OpenCalculator(const char *label, const float *valuePtr) : label(label), inputValue(valuePtr), inputValueType(ValueType::FLOAT) {}
        ImCalcInput::OpenCalculator::OpenCalculator(const char *label, const int *valuePtr) : label(label), inputValue(valuePtr), inputValueType(ValueType::INTEGER) {}

        void ImCalcInput::OpenCalculator::drawButton(Button button, const ImVec2 &size) {
            static char simpleLabelStr[2] = {0, 0};
            const char *labelStr;
            switch (button) {
                case Button::ENTER: labelStr = ICON_FA_EQUALS; break;
                case Button::BACKSPACE: labelStr = ICON_FA_BACKSPACE; break;
                default: labelStr = simpleLabelStr; simpleLabelStr[0] = static_cast<char>(button); break;
            }
            const auto tmp = getPlatformKeyIndex(button);
            const auto idxA = tmp.first, idxB = tmp.second;

            bool highlightButton = false, clickedButton = false, pressedKey = false;

            if (ImGui::IsWindowFocused()) {
                if ((idxA!=0 && ImGui::IsKeyPressed(idxA)) || (idxB!=0 && ImGui::IsKeyPressed(idxB))) {
                    pressedKey = true;
                    highlightButton = true;
                } else  if ((idxA!=0 && ImGui::IsKeyDown(idxA)) || (idxB!=0 && ImGui::IsKeyDown(idxB))) {
                    highlightButton = true;
                }
            }

            if (highlightButton) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
            }
            if (ImGui::Button(labelStr, size)) {
                clickedButton = true;
            }
            if (highlightButton) {
                ImGui::PopStyleColor();
            }

            if (clickedButton || (pressedKey && strchr(INPUT_QUEUE_HANDLED_BUTTONS, (char)button) == nullptr)) {
                buttonPressed(button);
            }
        }

        void ImCalcInput::OpenCalculator::buttonPressed(Button button) {
            if (currentInputTextEnd-currentInputText>=CURRENT_INPUT_TEXT_LENGTH) {
                //todo maybe display a warning
            } else if (Button::BACKSPACE==button) {
                --currentInputTextEnd;
                *currentInputTextEnd = '\0';
            } else if (Button::ENTER==button) {
                enterPressed();
            } else {
                *currentInputTextEnd = static_cast<char>(button);
                ++currentInputTextEnd;
                *currentInputTextEnd = '\0';
            }
        }

        void ImCalcInput::OpenCalculator::enterPressed() {
            std::cout << "TODO calculate " << currentInputText << std::endl;
            currentInputTextEnd = currentInputText;
            *currentInputTextEnd = '\0';
        }

        std::pair<int, int> ImCalcInput::OpenCalculator::getPlatformKeyIndex(Button button) {
#if IMCALCINPUT_PLATFORM==IMCALCINPUT_GLFW
            switch (button) {
                case Button::NUM_0: return {GLFW_KEY_0, GLFW_KEY_KP_0};
                case Button::NUM_1: return {GLFW_KEY_1, GLFW_KEY_KP_1};
                case Button::NUM_2: return {GLFW_KEY_2, GLFW_KEY_KP_2};
                case Button::NUM_3: return {GLFW_KEY_3, GLFW_KEY_KP_3};
                case Button::NUM_4: return {GLFW_KEY_4, GLFW_KEY_KP_4};
                case Button::NUM_5: return {GLFW_KEY_5, GLFW_KEY_KP_5};
                case Button::NUM_6: return {GLFW_KEY_6, GLFW_KEY_KP_6};
                case Button::NUM_7: return {GLFW_KEY_7, GLFW_KEY_KP_7};
                case Button::NUM_8: return {GLFW_KEY_8, GLFW_KEY_KP_8};
                case Button::NUM_9: return {GLFW_KEY_9, GLFW_KEY_KP_9};
                case Button::BACKSPACE: return {GLFW_KEY_BACKSPACE, 0};
                case Button::PLUS: return {GLFW_KEY_KP_ADD, 0};
                case Button::MINUS: return {GLFW_KEY_KP_SUBTRACT, 0};
                case Button::MULTIPLICATION: return {GLFW_KEY_KP_MULTIPLY, 0};
                case Button::DIVISION: return {GLFW_KEY_KP_DIVIDE, 0};
                case Button::ENTER: return {GLFW_KEY_ENTER, GLFW_KEY_KP_ENTER};
                default: return {0, 0};
            }
#else
#error set IMCALCINPUT_PLATFORM to a supported value
#endif
        }

        std::map<void*, std::unique_ptr<OpenCalculator>> openCalculators;
    }

    bool InputDouble(const char *label, double *v, double step, double step_fast, const char *format, ImGuiInputTextFlags flags) {
        const auto childLabelSize = 11 + strlen(label);
        char childLabel[childLabelSize];
        std::snprintf(childLabel, childLabelSize, "ImCalcInput%s", label);
        if (ImGui::BeginChild(childLabel)) {
            ImGui::InputDouble("", v, step, step_fast, format, flags);
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_CALCULATOR)) {
                auto it = openCalculators.find(v);
                if (it==openCalculators.end()) {
                    openCalculators[v] = std::make_unique<OpenCalculator>(label, v);
                } else {
                    it->second->focusNextTime();
                }
            }
            ImGui::SameLine();
            ImGui::Text("%s", label);
            ImGui::EndChild();
            return true;
        }
        return false;
    }

    void drawOpenCalculators() {
        for (const auto &calculator : openCalculators) {
            calculator.second->draw();
        }
    }
}