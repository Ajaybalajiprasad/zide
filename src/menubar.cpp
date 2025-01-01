#include "editor.h"
#include "imgui.h"
#include "utils.h"
#include "app.h"
#include "init.h"
#include <string>

void render_main_menu_bar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "CTRL+N")) {
      }
      if (ImGui::MenuItem("Open", "CTRL+O")) { 
      }
      if (ImGui::MenuItem("Export", "F2")) {
        save_screenshot(&app_state.editor_state);
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "CTRL+X")) {
        exit(0);
      }
    	if (ImGui::BeginMenu("Import")) {
      	if (ImGui::MenuItem("Color palete", "CTRL+SHIFT+C")) {
					std::string contents = open_file_dialog_return_contents_gpl();
					if(contents.size()>1){
						parse_gpl_file(contents, app_state.color_swatch_state);
					}
      	}
				ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {
      }
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
      }
      if (ImGui::MenuItem("Change Dimensions", "")) {
        app_state.editor_state.changing_dimensions = true;
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Windows")) {
      if (ImGui::MenuItem("Timeline", NULL, &app_state.is_timeline_visible)) {
      }
      if (ImGui::MenuItem("Toolbar", NULL, &app_state.is_toolbar_visible)) {
      }
      if (ImGui::MenuItem("ColorSwatch", NULL,
                          &app_state.is_colorswatch_visible)) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      app_state.show_about_dialog = true;
      ImGui::EndMenu();
    } 

    float windowWidth = ImGui::GetWindowWidth();
    float buttonWidth = 30.0f;
    ImGui::SameLine(windowWidth - buttonWidth - ImGui::GetStyle().WindowPadding.x);
    if (ImGui::Button("X", ImVec2(buttonWidth, 0))) {
      exit(0);
    }
    ImGui::EndMainMenuBar();
  }
  if (app_state.editor_state.changing_dimensions) {
    render_dimensions_select();
  }

  ImGuiIO& io = ImGui::GetIO();
  if ((io.KeyCtrl || (io.KeyMods & ImGuiKey_ModCtrl)) && ImGui::IsKeyPressed(ImGuiKey_X)) {
    exit(0);
  }

  if (app_state.show_about_dialog) {
        ImGui::Begin("About Zide", &app_state.show_about_dialog, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Zide is a Design environment\nVersion xx.x");
        ImGui::Text("Click");
        ImGui::SameLine();
        if (ImGui::Button("here")) {
          system("xdg-open https://github.com/bitspaceorg/zide");
        }
        ImGui::SameLine();
        ImGui::Text("to Know more About us.");
        ImGui::End();
    }
}
