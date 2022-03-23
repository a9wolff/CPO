#ifndef PROJET_STYLE_HPP
#define PROJET_STYLE_HPP


namespace imgui_render {

    void setCustomStyle()
    {
        ImGuiStyle* style = &ImGui::GetStyle();

        /* Colors */
        ImVec4* colors = style->Colors;

        colors[ImGuiCol_WindowBg]      = ImVec4(1., 1., 1., 1.00f); //background color
        colors[ImGuiCol_TitleBg]       = ImVec4(243./255., 243./255., 243./255., 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(243./255., 243./255., 243./255., 1.00f);
        colors[ImGuiCol_Text]          = ImVec4(0., 0., 0., 1.00f);


        /* Style */
        style->WindowRounding = 10.0f;
        style->FramePadding   = {10.0f, 8.0f};

        //Font: see imgui_draw.cpp l.2135 in function AddFontDefault();
    }

} //namespace imgui_render

#endif //PROJET_STYLE_HPP
