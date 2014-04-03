// t3d - Copyright (c) Gustav

#include "t3d/app.h"

#include <wx/docmdi.h>
#include <wx/cmdproc.h>
#include <wx/config.h>

#include "t3d/doc.h"
#include "t3d/view.h"

wxIMPLEMENT_APP(T3dApp);

void CreateMenuBarForFrame(wxFrame *frame, wxMenu *file, wxMenu *edit) {
  wxMenuBar *menubar = new wxMenuBar;

  menubar->Append(file, wxGetStockLabel(wxID_FILE));

  if (edit) menubar->Append(edit, wxGetStockLabel(wxID_EDIT));

  wxMenu *help = new wxMenu;
  help->Append(wxID_ABOUT);
  menubar->Append(help, wxGetStockLabel(wxID_HELP));

  frame->SetMenuBar(menubar);
}

wxMenu *CreateDrawingEditMenu() {
  wxMenu *const menu = new wxMenu;
  menu->Append(wxID_UNDO);
  menu->Append(wxID_REDO);
  menu->AppendSeparator();
  menu->Append(wxID_CUT, "&Cut last segment");

  return menu;
}

void AppendDocumentFileCommands(wxMenu *menu, bool supportsPrinting) {
  menu->Append(wxID_CLOSE);
  menu->Append(wxID_SAVE);
  menu->Append(wxID_SAVEAS);
  menu->Append(wxID_REVERT, _("Re&vert..."));

  if (supportsPrinting) {
    menu->AppendSeparator();
    menu->Append(wxID_PRINT);
    menu->Append(wxID_PRINT_SETUP, "Print &Setup...");
    menu->Append(wxID_PREVIEW);
  }
}

bool T3dApp::OnInit() {
  if (!wxApp::OnInit()) return false;

  ::wxInitAllImageHandlers();

  SetVendorName("madeso");
  SetAppName("t3d");
  SetAppDisplayName("Tiled 3d editor");

  wxDocManager *docManager = new wxDocManager;

  new wxDocTemplate(docManager, "Drawing", "*.t3d", "", "t3d",
                    "Tiled 3d document", "Tiled 3d View", CLASSINFO(Doc),
                    CLASSINFO(View));
#if defined(__WXMAC__) && wxOSX_USE_CARBON
  wxFileName::MacRegisterDefaultTypeAndCreator("t3d", 'WXMB', 'WXMA');
#endif

  // create the main frame window
  wxFrame *frame;
  frame =
      new wxDocMDIParentFrame(docManager, NULL, wxID_ANY, GetAppDisplayName(),
                              wxDefaultPosition, wxSize(500, 400));

  // and its menu bar
  wxMenu *menuFile = new wxMenu;

  menuFile->Append(wxID_NEW);
  menuFile->Append(wxID_OPEN);

  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  // A nice touch: a history of files visited. Use this menu.
  docManager->FileHistoryUseMenu(menuFile);
#if wxUSE_CONFIG
  docManager->FileHistoryLoad(*wxConfig::Get());
#endif  // wxUSE_CONFIG

  CreateMenuBarForFrame(frame, menuFile, NULL);

  frame->SetIcon(wxICON(doc));
  frame->Centre();
  frame->Show();

  return true;
}

wxFrame *T3dApp::CreateChildFrame(wxView *view) {
  // create a child frame of appropriate class for the current mode

  wxDocument *doc = view->GetDocument();
  wxFrame *subframe = new wxDocMDIChildFrame(
      doc, view, wxStaticCast(GetTopWindow(), wxDocMDIParentFrame), wxID_ANY,
      "Child Frame", wxDefaultPosition, wxSize(300, 300));

  wxMenu *menuFile = new wxMenu;

  menuFile->Append(wxID_NEW);
  menuFile->Append(wxID_OPEN);
  AppendDocumentFileCommands(menuFile, true);
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuEdit = CreateDrawingEditMenu();

  doc->GetCommandProcessor()->SetEditMenu(menuEdit);
  doc->GetCommandProcessor()->Initialize();

  CreateMenuBarForFrame(subframe, menuFile, menuEdit);

  // subframe->SetIcon(isCanvas ? wxICON(chrt) : wxICON(notepad));

  return subframe;
}
