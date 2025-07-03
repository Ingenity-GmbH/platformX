#include "include/util.h"

void util::setFont(const PXHandle& handle) {
    HFONT hFont = CreateFont(
        18,                        // Height
        0,                         // Width
        0,                         // Escapement
        0,                         // Orientation
        FW_NORMAL,                 // Weight
        FALSE,                     // Italic
        FALSE,                     // Underline
        0,                         // StrikeOut
        ANSI_CHARSET,              // CharSet
        OUT_DEFAULT_PRECIS,        // OutPrecision
        CLIP_DEFAULT_PRECIS,       // ClipPrecision
        DEFAULT_QUALITY,           // Quality
        DEFAULT_PITCH | FF_SWISS,  // PitchAndFamily
        WIN_STANDARD_FONT          // Facename
    );
    SendMessage(handle, WM_SETFONT, (WPARAM)hFont, TRUE);
}
void util::setTitle(const PXHandle& handle, const PXString& title) {
    SendMessage(handle, WM_SETTEXT, 0, (LPARAM)(title.toLPCWSTR()));
}

PXString util::getTitle(const PXHandle& handle) {
    int titleLen = SendMessage(handle, WM_GETTEXTLENGTH, 0, 0);

    if (titleLen <= 0)
        return PXString();

    std::wstring buffer(titleLen, L'\0');
    SendMessage(handle, WM_GETTEXT, (WPARAM)(titleLen+1), (LPARAM)buffer.data());
    
    // remove any trailing nulls (if present)
    buffer.resize(wcsnlen(buffer.data(), buffer.size()));

    return PXString(buffer);
}

void util::setWindowState(const PXHandle& handle, const int32_t& state) {
    ShowWindow(handle, (int)state);
}

void util::setState(const PXHandle& handle, const bool& state) {
    if (state)
        SendMessage(handle, BM_SETCHECK, BST_CHECKED, 0);
    else
        SendMessage(handle, BM_SETCHECK, BST_UNCHECKED, 0);
}

bool util::getState(const PXHandle& handle) {
    auto state = SendMessage(handle, BM_GETCHECK, 0, 0);
    return state==BST_CHECKED ? true : false;
}

void LIB util::toggleState(const PXHandle& handle) {
    if (getState(handle))
        setState(handle, false);
    else
        setState(handle, true);
}

void local_addNode(const PXHandle& handle, PXNode& node) {
    static std::vector<std::pair<PXString,PXNodeHandle>> created;
    TVINSERTSTRUCTW tvis = {};

    auto it = std::find_if(created.begin(), created.end(), [&node](const std::pair<PXString,PXNodeHandle>& pair) { return !node.title.toString().compare(pair.first.toString()); });
    if (it != created.end())
        return;

    if (node.parent) {
        auto it = std::find_if(created.begin(), created.end(), [&node](const std::pair<PXString,PXNodeHandle>& pair) { return !node.parent->title.toString().compare(pair.first.toString()); });
        if (it != created.end()) {
            tvis.hParent = (*it).second;
        }
    }
    else
        tvis.hParent = TVI_ROOT; 

    tvis.hInsertAfter = TVI_LAST;
    tvis.item.mask = TVIF_TEXT;
    tvis.item.pszText = (LPWSTR)node.title.toLPCWSTR();
    node.handle = reinterpret_cast<PXNodeHandle>(SendMessage(handle, TVM_INSERTITEMW, 0, (LPARAM)&tvis));

    if (node.parent)
        SendMessage(handle, TVM_EXPAND, TVE_EXPAND, (LPARAM)tvis.hParent);
    
    created.push_back(std::make_pair(node.title, node.handle));
}

void util::addNodes(const PXHandle& handle, std::vector<PXNode>& nodes, const PXType& type) {
    switch (type) {
        case TREEVIEW: {
            for (auto& node : nodes)
                local_addNode(handle, node);
        }
        default: {
            SendMessage(handle, LB_RESETCONTENT, 0, 0);
            SendMessage(handle, CB_RESETCONTENT, 0, 0);

            for (size_t i=0; i<nodes.size(); i++) {
                SendMessageW(handle, LB_INSERTSTRING, static_cast<WPARAM>(i), reinterpret_cast<LPARAM>(nodes[i].title.toLPCWSTR()));
                SendMessageW(handle, CB_INSERTSTRING, static_cast<WPARAM>(i), reinterpret_cast<LPARAM>(nodes[i].title.toLPCWSTR()));
            }
        }
    }
}

size_t util::getSelectedNode(const PXHandle& handle, const PXType& type) {
    switch (type) {
        case LISTBOX:
            return SendMessage(handle, LB_GETCURSEL, 0, 0);
        case COMBOBOX:
            return SendMessage(handle, CB_GETCURSEL, 0, 0);
        case TREEVIEW:
            return reinterpret_cast<size_t>(TreeView_GetSelection(handle));
    } 
    return -1;
}

void util::addPart(PXControl& self, std::vector<PXStatusBarPart>& parts, const double& relEndPos, const PXString& text) {
    auto it = std::find_if(parts.begin(), parts.end()-1, [&relEndPos](const PXStatusBarPart& part) { return relEndPos < part.relEndPos; });
    double pos = std::min<double>(std::max<double>(0.0, relEndPos), 0.9);
    parts.insert(it, {pos, text});
    updateParts(self, parts);
}

void util::updateParts(PXControl& self, std::vector<PXStatusBarPart>& parts) {
    uint32_t width = self.getSize().width;
    PXHandle handle = self.getHandle();
    size_t partsSize = parts.size();

    int* pParts = new int[partsSize];
    for (size_t i=0; i<parts.size(); i++)
        pParts[i] = std::max<int>(parts[i].relEndPos * width, -1);
    SendMessage(handle, SB_SETPARTS, partsSize, reinterpret_cast<LPARAM>(pParts));
    delete[] pParts;

    for (size_t idx=0; idx<partsSize; idx++)
        SendMessage(handle, SB_SETTEXT, idx, reinterpret_cast<LPARAM>(parts[idx].text.toLPCWSTR()));
}
