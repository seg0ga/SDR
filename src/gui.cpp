#include "gui.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <algorithm>
#include <cmath>
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

static void apply_theme(bool dark) {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding    = 6.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;

    style.WindowPadding     = ImVec2(10.0f, 10.0f);
    style.FramePadding      = ImVec2(8.0f, 6.0f);
    style.ItemSpacing       = ImVec2(8.0f, 7.0f);
    style.ItemInnerSpacing  = ImVec2(6.0f, 4.0f);
    style.WindowBorderSize  = 0.0f;
    style.ChildBorderSize   = 1.0f;
    style.FrameBorderSize   = 1.0f;

    ImVec4 *c = style.Colors;
    ImPlotStyle &plot_style = ImPlot::GetStyle();
    plot_style.PlotBorderSize = 1.0f;
    plot_style.PlotRounding   = 4.0f;
    plot_style.LineWeight     = 1.6f;

    if (dark) {
        c[ImGuiCol_WindowBg]             = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
        c[ImGuiCol_ChildBg]              = ImVec4(0.12f, 0.13f, 0.16f, 1.00f);
        c[ImGuiCol_PopupBg]              = ImVec4(0.14f, 0.16f, 0.20f, 0.98f);
        c[ImGuiCol_Border]               = ImVec4(0.20f, 0.23f, 0.28f, 1.00f);
        c[ImGuiCol_FrameBg]              = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
        c[ImGuiCol_FrameBgHovered]       = ImVec4(0.16f, 0.18f, 0.23f, 1.00f);
        c[ImGuiCol_FrameBgActive]        = ImVec4(0.20f, 0.24f, 0.30f, 1.00f);
        c[ImGuiCol_TitleBg]              = ImVec4(0.09f, 0.10f, 0.12f, 1.00f);
        c[ImGuiCol_TitleBgActive]        = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
        c[ImGuiCol_ScrollbarBg]          = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
        c[ImGuiCol_ScrollbarGrab]        = ImVec4(0.22f, 0.26f, 0.32f, 1.00f);
        c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.33f, 0.40f, 1.00f);
        c[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.35f, 0.42f, 0.50f, 1.00f);
        c[ImGuiCol_CheckMark]            = ImVec4(0.24f, 0.70f, 0.98f, 1.00f);
        c[ImGuiCol_SliderGrab]           = ImVec4(0.24f, 0.70f, 0.98f, 1.00f);
        c[ImGuiCol_SliderGrabActive]     = ImVec4(0.38f, 0.80f, 1.00f, 1.00f);
        c[ImGuiCol_Button]               = ImVec4(0.16f, 0.18f, 0.23f, 1.00f);
        c[ImGuiCol_ButtonHovered]        = ImVec4(0.22f, 0.27f, 0.35f, 1.00f);
        c[ImGuiCol_ButtonActive]         = ImVec4(0.28f, 0.35f, 0.45f, 1.00f);
        c[ImGuiCol_Header]               = ImVec4(0.18f, 0.22f, 0.28f, 1.00f);
        c[ImGuiCol_HeaderHovered]        = ImVec4(0.24f, 0.30f, 0.38f, 1.00f);
        c[ImGuiCol_HeaderActive]         = ImVec4(0.28f, 0.36f, 0.46f, 1.00f);
        c[ImGuiCol_Separator]            = ImVec4(0.20f, 0.23f, 0.28f, 1.00f);
        c[ImGuiCol_Text]                 = ImVec4(0.92f, 0.94f, 0.96f, 1.00f);
        c[ImGuiCol_TextDisabled]         = ImVec4(0.52f, 0.56f, 0.62f, 1.00f);

        plot_style.Colors[ImPlotCol_PlotBg]       = ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
        plot_style.Colors[ImPlotCol_PlotBorder]   = ImVec4(0.20f, 0.23f, 0.28f, 1.00f);
        plot_style.Colors[ImPlotCol_LegendBg]     = ImVec4(0.10f, 0.11f, 0.14f, 0.88f);
        plot_style.Colors[ImPlotCol_LegendBorder] = ImVec4(0.20f, 0.23f, 0.28f, 0.80f);
        plot_style.Colors[ImPlotCol_AxisGrid]     = ImVec4(0.16f, 0.18f, 0.23f, 0.65f);
        plot_style.Colors[ImPlotCol_AxisTxt]      = ImVec4(0.72f, 0.76f, 0.82f, 1.00f);
        plot_style.Colors[ImPlotCol_TitleText]    = ImVec4(0.92f, 0.94f, 0.96f, 1.00f);
    } else {
        c[ImGuiCol_WindowBg]             = ImVec4(0.94f, 0.95f, 0.97f, 1.00f);
        c[ImGuiCol_ChildBg]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        c[ImGuiCol_PopupBg]              = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
        c[ImGuiCol_Border]               = ImVec4(0.82f, 0.85f, 0.90f, 1.00f);
        c[ImGuiCol_FrameBg]              = ImVec4(0.96f, 0.97f, 0.98f, 1.00f);
        c[ImGuiCol_FrameBgHovered]       = ImVec4(0.90f, 0.92f, 0.96f, 1.00f);
        c[ImGuiCol_FrameBgActive]        = ImVec4(0.84f, 0.88f, 0.94f, 1.00f);
        c[ImGuiCol_TitleBg]              = ImVec4(0.92f, 0.94f, 0.97f, 1.00f);
        c[ImGuiCol_TitleBgActive]        = ImVec4(0.88f, 0.91f, 0.95f, 1.00f);
        c[ImGuiCol_ScrollbarBg]          = ImVec4(0.94f, 0.95f, 0.97f, 1.00f);
        c[ImGuiCol_ScrollbarGrab]        = ImVec4(0.75f, 0.78f, 0.84f, 1.00f);
        c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.65f, 0.70f, 0.78f, 1.00f);
        c[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.55f, 0.60f, 0.70f, 1.00f);
        c[ImGuiCol_CheckMark]            = ImVec4(0.12f, 0.48f, 0.90f, 1.00f);
        c[ImGuiCol_SliderGrab]           = ImVec4(0.12f, 0.48f, 0.90f, 1.00f);
        c[ImGuiCol_SliderGrabActive]     = ImVec4(0.08f, 0.40f, 0.80f, 1.00f);
        c[ImGuiCol_Button]               = ImVec4(0.92f, 0.94f, 0.97f, 1.00f);
        c[ImGuiCol_ButtonHovered]        = ImVec4(0.85f, 0.89f, 0.95f, 1.00f);
        c[ImGuiCol_ButtonActive]         = ImVec4(0.78f, 0.84f, 0.92f, 1.00f);
        c[ImGuiCol_Header]               = ImVec4(0.88f, 0.92f, 0.97f, 1.00f);
        c[ImGuiCol_HeaderHovered]        = ImVec4(0.82f, 0.88f, 0.95f, 1.00f);
        c[ImGuiCol_HeaderActive]         = ImVec4(0.76f, 0.82f, 0.90f, 1.00f);
        c[ImGuiCol_Separator]            = ImVec4(0.84f, 0.87f, 0.92f, 1.00f);
        c[ImGuiCol_Text]                 = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
        c[ImGuiCol_TextDisabled]         = ImVec4(0.48f, 0.52f, 0.58f, 1.00f);

        plot_style.Colors[ImPlotCol_PlotBg]       = ImVec4(0.98f, 0.99f, 1.00f, 1.00f);
        plot_style.Colors[ImPlotCol_PlotBorder]   = ImVec4(0.82f, 0.85f, 0.90f, 1.00f);
        plot_style.Colors[ImPlotCol_LegendBg]     = ImVec4(1.00f, 1.00f, 1.00f, 0.92f);
        plot_style.Colors[ImPlotCol_LegendBorder] = ImVec4(0.82f, 0.85f, 0.90f, 0.80f);
        plot_style.Colors[ImPlotCol_AxisGrid]     = ImVec4(0.86f, 0.89f, 0.93f, 0.80f);
        plot_style.Colors[ImPlotCol_AxisTxt]      = ImVec4(0.24f, 0.28f, 0.34f, 1.00f);
        plot_style.Colors[ImPlotCol_TitleText]    = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    }
}

void run_gui(SignalData &data) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow(
        "SDR Transceiver",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 680,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    static bool dark_mode = true;
    apply_theme(dark_mode);

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330");

    static double freq1 = 800.0;
    static double freq2 = 850.0;
    static double sample_rate = 1.0;
    static int amplitude = 1500;
    static int rx_gain = 50;
    static int tx_gain = 50;
    static int mod_mode = 0; // 0 - BPSK, 1 - QPSK

    const ImPlotFlags plot_flags = ImPlotFlags_NoMenus;

    while (data.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT ||
                (event.type == SDL_WINDOWEVENT &&
                 event.window.event == SDL_WINDOWEVENT_CLOSE &&
                 event.window.windowID == SDL_GetWindowID(window))) {
                data.running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::Begin("MainLayout", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings);

        ImGui::BeginChild("TopHeader", ImVec2(0, 34.0f), false);
        {
            ImGui::AlignTextToFramePadding();
            ImGui::TextUnformatted("PLUTO SDR");

            const float btn_w = 110.0f;
            ImGui::SameLine(ImGui::GetWindowWidth() - btn_w - ImGui::GetStyle().WindowPadding.x);
            if (ImGui::Button(dark_mode ? "Тёмная" : "Светлая", ImVec2(btn_w, 24.0f))) {
                dark_mode = !dark_mode;
                apply_theme(dark_mode);
            }
        }
        ImGui::EndChild();
        ImGui::Separator();
        ImGui::Spacing();

        const ImVec2 available = ImGui::GetContentRegionAvail();

        const float settings_w = std::clamp(available.x * 0.25f, 220.0f, 320.0f);
        const float plots_total_w = available.x - settings_w - ImGui::GetStyle().ItemSpacing.x;
        const float plot_w = (plots_total_w - ImGui::GetStyle().ItemSpacing.x) / 2.0f;

        ImGui::BeginChild("SettingsPanel", ImVec2(settings_w, available.y), true);
        {
            ImGui::TextUnformatted("Настройки");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextDisabled("Частота 1 (Freq 1)");
            ImGui::SetNextItemWidth(-50.0f);
            ImGui::InputDouble("##freq1", &freq1, 1.0, 10.0, "%.3f");
            ImGui::SameLine();
            ImGui::TextUnformatted("МГц");

            ImGui::Spacing();
            ImGui::TextDisabled("Частота 2 (Freq 2)");
            ImGui::SetNextItemWidth(-50.0f);
            ImGui::InputDouble("##freq2", &freq2, 1.0, 10.0, "%.3f");
            ImGui::SameLine();
            ImGui::TextUnformatted("МГц");

            ImGui::Spacing();
            ImGui::TextDisabled("Частота дискретизации");
            ImGui::SetNextItemWidth(-50.0f);
            ImGui::InputDouble("##sample_rate", &sample_rate, 0.5, 1.0, "%.3f");
            ImGui::SameLine();
            ImGui::TextUnformatted("МГц");

            ImGui::Spacing();
            ImGui::TextDisabled("Амплитуда");
            ImGui::SetNextItemWidth(-1);
            ImGui::SliderInt("##amplitude", &amplitude, 0, 4000, "%d");

            ImGui::Spacing();
            ImGui::TextDisabled("Усиление приёма (RX Gain)");
            ImGui::SetNextItemWidth(-1);
            ImGui::SliderInt("##rx_gain", &rx_gain, 0, 75, "%d дБ");

            ImGui::Spacing();
            ImGui::TextDisabled("Усиление передачи (TX Gain)");
            ImGui::SetNextItemWidth(-1);
            ImGui::SliderInt("##tx_gain", &tx_gain, 0, 75, "%d дБ");

            ImGui::Spacing();
            ImGui::TextDisabled("Режим передачи");

            const float seg_w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) / 2.0f;
            if (mod_mode == 0) {
                ImGui::PushStyleColor(ImGuiCol_Button, dark_mode ? ImVec4(0.20f, 0.55f, 0.88f, 1.0f) : ImVec4(0.12f, 0.48f, 0.90f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            }
            if (ImGui::Button("BPSK", ImVec2(seg_w, 24.0f))) mod_mode = 0;
            if (mod_mode == 0) ImGui::PopStyleColor(2);

            ImGui::SameLine();
            if (mod_mode == 1) {
                ImGui::PushStyleColor(ImGuiCol_Button, dark_mode ? ImVec4(0.20f, 0.55f, 0.88f, 1.0f) : ImVec4(0.12f, 0.48f, 0.90f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            }
            if (ImGui::Button("QPSK", ImVec2(seg_w, 24.0f))) mod_mode = 1;
            if (mod_mode == 1) ImGui::PopStyleColor(2);
        }
        ImGui::EndChild();

        ImGui::SameLine();

        const int count = static_cast<int>(data.samples.size());

        const ImVec4 col_i    = dark_mode ? ImVec4(0.20f, 0.75f, 1.00f, 0.90f) : ImVec4(0.05f, 0.50f, 0.85f, 0.95f);
        const ImVec4 col_q    = dark_mode ? ImVec4(1.00f, 0.60f, 0.20f, 0.90f) : ImVec4(0.88f, 0.45f, 0.05f, 0.95f);
        const ImVec4 col_mag  = dark_mode ? ImVec4(0.20f, 0.85f, 0.55f, 0.95f) : ImVec4(0.08f, 0.65f, 0.40f, 0.95f);
        const ImVec4 col_dots = dark_mode ? ImVec4(0.20f, 0.75f, 1.00f, 0.85f) : ImVec4(0.05f, 0.50f, 0.85f, 0.85f);

        if (ImPlot::BeginPlot("Созвездие (I и Q)", ImVec2(plot_w, available.y),
                             plot_flags | ImPlotFlags_NoLegend | ImPlotFlags_Equal)) {
            ImPlot::SetupAxes("I", "Q");
            ImPlot::SetupAxesLimits(-2500, 2500, -2500, 2500);

            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 2.5f, col_dots, 1.0f, col_dots);
            ImPlot::PlotScatterG("IQ", [](int index, void *ptr) {
                auto &signal = *static_cast<SignalData *>(ptr);
                return ImPlotPoint(signal.samples[index].real(), signal.samples[index].imag());
            }, &data, count);
            ImPlot::EndPlot();
        }

        ImGui::SameLine();

        ImPlot::SetNextAxesToFit();
        if (ImPlot::BeginPlot("Амплитуда от времени", ImVec2(plot_w, available.y), plot_flags)) {
            ImPlot::SetupAxes("Время, мс", "Амплитуда");

            ImPlot::SetNextLineStyle(col_i, 1.5f);
            ImPlot::PlotLineG("I", [](int index, void *ptr) {
                auto &signal = *static_cast<SignalData *>(ptr);
                return ImPlotPoint(1000.0 * index / signal.sample_rate, signal.samples[index].real());
            }, &data, count);

            ImPlot::SetNextLineStyle(col_q, 1.5f);
            ImPlot::PlotLineG("Q", [](int index, void *ptr) {
                auto &signal = *static_cast<SignalData *>(ptr);
                return ImPlotPoint(1000.0 * index / signal.sample_rate, signal.samples[index].imag());
            }, &data, count);

            ImPlot::SetNextLineStyle(col_mag, 1.8f);
            ImPlot::PlotLineG("|IQ|", [](int index, void *ptr) {
                auto &signal = *static_cast<SignalData *>(ptr);
                return ImPlotPoint(1000.0 * index / signal.sample_rate, std::abs(signal.samples[index]));
            }, &data, count);
            ImPlot::EndPlot();
        }

        ImGui::End();

        ImGui::Render();
        int width_pixels, height_pixels;
        SDL_GL_GetDrawableSize(window, &width_pixels, &height_pixels);
        glViewport(0, 0, width_pixels, height_pixels);

        if (dark_mode) {
            glClearColor(0.09f, 0.10f, 0.12f, 1.0f);
        } else {
            glClearColor(0.94f, 0.95f, 0.97f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
