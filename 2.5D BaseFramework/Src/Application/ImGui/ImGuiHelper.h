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

	void RegisterFunction( const char* _name,std::function<void(void)> _func)
	{
		m_functions[_name]= _func;
	};

	//ウィンドウ描画
	void ImGuiUpdate()
	{
		ImGui::SetNextWindowPos(ImVec2(20, 20), (ImGuiCond)2);
		ImGui::SetNextWindowSize(ImVec2(100, 200), (ImGuiCond)2);

		ImGui::Begin((const char*)"Buttons");
		
		auto it = m_functions.begin();
		while(it!=m_functions.end())
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
	std::unordered_map<const char*,std::function<void(void)>> m_functions;

	ImGuiFunctionButton() {};
	~ImGuiFunctionButton() {};

public:
	static ImGuiFunctionButton& GetInstance()
	{
		static ImGuiFunctionButton inst;
		return inst;
	}
};