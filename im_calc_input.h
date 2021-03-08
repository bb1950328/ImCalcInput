//
// Created by bb1950328 on 08.03.2021.
//

#ifndef IMCALCINPUTTESTING_IM_CALC_INPUT_H
#define IMCALCINPUTTESTING_IM_CALC_INPUT_H

#include <imgui.h>
#include <utility>

namespace ImCalcInput {

    namespace {
        enum class ValueType {
            INTEGER,
            FLOAT,
            DOUBLE,
        };
        enum class Button : char {
            NUM_0 = '0',
            NUM_1 = '1',
            NUM_2 = '2',
            NUM_3 = '3',
            NUM_4 = '4',
            NUM_5 = '5',
            NUM_6 = '6',
            NUM_7 = '7',
            NUM_8 = '8',
            NUM_9 = '9',
            BACKSPACE = '\b',
            ROUND_BRACKET_OPEN = '(',
            ROUND_BRACKET_CLOSE = ')',
            SQUARE_BRACKET_OPEN = '[',
            SQUARE_BRACKET_CLOSE = ']',
            PLUS = '+',
            MINUS = '-',
            MULTIPLICATION = '*',
            DIVISION = '/',
            ENTER = '\n'
        };

        const char* INPUT_QUEUE_HANDLED_BUTTONS = "0123456789()[]+-*/";

        class OpenCalculator {
            const char* label;
            const void* const inputValue;
            const ValueType inputValueType;
            bool isFocusNextTime = false;

            static constexpr int CURRENT_INPUT_TEXT_LENGTH = 256;
            char currentInputText[CURRENT_INPUT_TEXT_LENGTH] = {0};
            char* currentInputTextEnd = currentInputText;

            void buttonPressed(Button button);
            void enterPressed();
            void drawButton(Button button, const ImVec2 &size);
            std::pair<int, int> getPlatformKeyIndex(Button button);

        public:
            void draw();
            void focusNextTime();

            explicit OpenCalculator(const char *label, const double *valuePtr);
            explicit OpenCalculator(const char *label, const float *valuePtr);
            explicit OpenCalculator(const char *label, const int *valuePtr);

        };
    }

    bool InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);

    void drawOpenCalculators();
}

#define IMCALCINPUT_GLFW 0
//todo define other libraries

#ifndef IMCALCINPUT_PLATFORM
//override this variable if you aren't using GLFW
#define IMCALCINPUT_PLATFORM IMCALCINPUT_GLFW
#endif

#endif //IMCALCINPUTTESTING_IM_CALC_INPUT_H
