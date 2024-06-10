#pragma once

//ヘルプツールチップ表示関数
// ・text			表示文字列
// ・showIcon       true:(?)を表示しその上にマウスが来たら表示
//						false:現在のコントロールの上にマウスが来たら表示
//-------------使用例--------------------------------------
//ツリーノード
//bTreeOpen = ImGui::TreeNodeEx((void*)2,flags,"Title Image");
//説明表示
//ImGuiShowHelp(u8"Ctrl+マウスホイール : 順番入れ替え\n右クリック : メニュー表示",false);
//if(bTreeOpen){
//...
inline void ImGuiShowHelp(const std::string& text, bool showIcon = false)
{
	if (showIcon)
	{
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(text.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

//=========================
//ログウィンドウクラス
//=========================
class ImGuiLogWindow
{
public:
	//ログをクリア
	void Clear() { m_buf.clear(); }

	//文字列を追加
	template<class... Args>
	void AddLog(const char* fmt, Args...args)
	{
		//改行を加える
		std::string str = fmt;
		str += "\n";
		m_buf.appendf(str.c_str(), args...);
		m_scrollToBottom = true;
	}

	//ウィンドウ描画
	void ImGuiUpdate(bool* p_opened = NULL)
	{
		ImGui::Begin((const char*)"Log Window", p_opened);
		ImGui::TextUnformatted(m_buf.begin());
		if (m_scrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		m_scrollToBottom = false;
		ImGui::End();
	}

private:
	ImGuiTextBuffer m_buf;
	bool m_scrollToBottom = false;

	ImGuiLogWindow() {};
	~ImGuiLogWindow() {};

public:
	static ImGuiLogWindow& GetInstance()
	{
		static ImGuiLogWindow inst;
		return inst;
	}
};

using LogWnd = ImGuiLogWindow;


class ImGuiFunctionButton
{
public:

	void RegisterFunction(const char* _name, std::function<void(void)> _func)
	{
		m_functions[_name] = _func;
	};

	//ウィンドウ描画
	void ImGuiUpdate()
	{
		ImGui::SetNextWindowPos(ImVec2(20, 20), (ImGuiCond)2);
		ImGui::SetNextWindowSize(ImVec2(100, 200), (ImGuiCond)2);

		ImGui::Begin((const char*)"Buttons");

		auto it = m_functions.begin();
		while (it != m_functions.end())
		{
			if (ImGui::Button((*it).first))
			{
				(*it).second();
			}

			it++;
		}

		ImGui::End();
	}

	void Clear()
	{
		m_functions.clear();
	};

private:
	std::unordered_map<const char*, std::function<void(void)>> m_functions;

	ImGuiFunctionButton() {};
	~ImGuiFunctionButton() {};

public:
	static ImGuiFunctionButton& GetInstance()
	{
		static ImGuiFunctionButton inst;
		return inst;
	}
};

class ImGuiSlider
{
public:

	void RegisterSliderFloat(const char* _name,float _min,float _max,float*_value)
	{
		SliderValueFloat s;
		s.min = _min;
		s.max = _max;
		s.value = _value;

		m_floatSliders[_name] = s;
	};

	void RegisterSliderInt(const char* _name, int _min, int _max, int* _value)
	{
		SliderValueInt s;
		s.min = _min;
		s.max = _max;
		s.value = _value;

		m_intSliders[_name] = s;
	};

	//ウィンドウ描画
	void ImGuiUpdate()
	{
		ImGui::SetNextWindowPos(ImVec2(20, 20), (ImGuiCond)2);
		ImGui::SetNextWindowSize(ImVec2(100, 200), (ImGuiCond)2);

		ImGui::Begin((const char*)"Sliders");

		auto it_slider = m_floatSliders.begin();
		while (it_slider != m_floatSliders.end())
		{
			ImGui::SliderFloat((*it_slider).first, (*it_slider).second.value, (*it_slider).second.min, (*it_slider).second.max);

			it_slider++;
		}

		auto it_int = m_intSliders.begin();
		while (it_int != m_intSliders.end())
		{
			ImGui::SliderInt((*it_int).first, (*it_int).second.value, (*it_int).second.min, (*it_int).second.max);

			it_int++;
		}

		ImGui::End();
	}

	void Clear()
	{
		m_floatSliders.clear();
	};

private:
	struct SliderValueFloat
	{
		float min = 0.0f;
		float max = 1.0f;
		float* value;
	};

	struct SliderValueInt
	{
		int min = 0;
		int max = 1;
		int* value;
	};

	std::unordered_map<const char*, SliderValueFloat> m_floatSliders;
	std::unordered_map<const char*, SliderValueInt> m_intSliders;

	ImGuiSlider() {};
	~ImGuiSlider() {};

public:
	static ImGuiSlider& GetInstance()
	{
		static ImGuiSlider inst;
		return inst;
	}
};

class ImGuiShaderManager
{
public:

	//ウィンドウ描画
	void ImGuiUpdate()
	{
		ImGui::SetNextWindowPos(ImVec2(400, 20), (ImGuiCond)2);
		ImGui::SetNextWindowSize(ImVec2(100, 200), (ImGuiCond)2);

		//ImGui::Begin((const char*)"Shader");

		if (ImGui::TreeNode("Bright"))
		{
			static float brightThreshold = 1.2;
			if (ImGui::SliderFloat((const char*)u8"閾値", &brightThreshold, -0.5, 1.0))
			{
				KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(brightThreshold);

			}

			ImGui::TreePop();
		}


		if (ImGui::TreeNode("Fog"))
		{
			static bool IsEnableDistanceFog = false;
			static bool IsEnableHeightFog = false;

			if (ImGui::Checkbox((const char*)u8"距離フォグ有効", &IsEnableDistanceFog))
				KdShaderManager::Instance().WorkAmbientController().SetFogEnable(IsEnableDistanceFog, IsEnableHeightFog);

			if (ImGui::Checkbox((const char*)u8"高さフォグ有効", &IsEnableHeightFog))
				KdShaderManager::Instance().WorkAmbientController().SetFogEnable(IsEnableDistanceFog, IsEnableHeightFog);

			static float DistanceFogDensity = 0.001f;

			if (ImGui::SliderFloat((const char*)u8"距離フォグ密度", &DistanceFogDensity, 0.0f,0.02f))
				KdShaderManager::Instance().WorkAmbientController().SetDistanceFog(Math::Vector3{ 1,1,1 }, DistanceFogDensity);


			ImGui::TreePop();
		}



		//ImGui::End();
	}


public:

	ImGuiShaderManager() {};
	~ImGuiShaderManager() {};

};