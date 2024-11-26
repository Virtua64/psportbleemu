#pragma once

#include <vector>
#include <string>
#include <set>

#include "ext/imgui/imgui.h"

#include "Common/CommonTypes.h"
#include "Common/Log.h"
#include "Common/System/Request.h"

#include "Core/Core.h"

#include "Core/Debugger/DisassemblyManager.h"
#include "Core/Debugger/DebugInterface.h"

#include "UI/ImDebugger/ImDisasmView.h"
#include "UI/ImDebugger/ImStructViewer.h"
#include "UI/ImDebugger/ImGe.h"
#include "UI/ImDebugger/ImConsole.h"

// This is the main state container of the whole Dear ImGUI-based in-game cross-platform debugger.
//
// Code conventions for ImGUI in PPSSPP
// * If windows/objects need state, prefix the class name with Im and just store straight in parent struct

class MIPSDebugInterface;
class GPUDebugInterface;

// Corresponds to the CDisasm dialog
class ImDisasmWindow {
public:
	void Draw(MIPSDebugInterface *mipsDebug, bool *open, CoreState coreState);
	ImDisasmView &View() {
		return disasmView_;
	}
	void DirtySymbolMap() {
		symsDirty_ = true;
	}
private:
	// We just keep the state directly in the window. Can refactor later.

	enum {
		INVALID_ADDR = 0xFFFFFFFF,
	};

	u32 gotoAddr_ = 0x1000;

	// Symbol cache
	std::vector<SymbolEntry> symCache_;
	bool symsDirty_ = true;
	int selectedSymbol_ = -1;
	char selectedSymbolName_[128];

	ImDisasmView disasmView_;
	char searchTerm_[64]{};
};

struct ImConfig {
	bool disasmOpen = true;
	bool demoOpen  = false;
	bool regsOpen = true;
	bool threadsOpen = true;
	bool callstackOpen = true;
	bool breakpointsOpen = false;
	bool modulesOpen = true;
	bool hleModulesOpen = false;
	bool atracOpen = true;
	bool structViewerOpen = false;
	bool framebuffersOpen = false;
	bool styleEditorOpen = false;
	bool filesystemBrowserOpen = false;
	bool kernelObjectsOpen = false;

	// HLE explorer settings
	// bool filterByUsed = true;

	// Various selections
	int selectedModule = 0;
	int selectedThread = 0;
	int selectedFramebuffer = -1;
	int selectedBreakpoint = -1;
	int selectedMemCheck = -1;
};

enum ImUiCmd {
	TRIGGER_FIND_POPUP = 0,
};

struct ImUiCommand {
	ImUiCmd cmd;
};

struct ImDebugger {
	ImDebugger();
	void Frame(MIPSDebugInterface *mipsDebug, GPUDebugInterface *gpuDebug);

	RequesterToken reqToken_;

	ImDisasmWindow disasm_;
	ImStructViewer structViewer_;

	// Open variables.
	ImConfig cfg_;
	ImConsole luaConsole_;

	// Open variables.
	bool disasmOpen_ = true;
	bool demoOpen_ = false;
	bool regsOpen_ = true;
	bool threadsOpen_ = true;
	bool callstackOpen_ = true;
	bool modulesOpen_ = true;
	bool consoleOpen_ = true;
};
