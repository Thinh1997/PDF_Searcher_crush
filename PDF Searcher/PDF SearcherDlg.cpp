
// PDF SearcherDlg.cpp : implementation file
//

#include "framework.h"
#include "PDF Searcher.h"
#include "PDF SearcherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#undef max
#undef min

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPDFSearcherDlg dialog



CPDFSearcherDlg::CPDFSearcherDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PDF_SEARCHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPDFSearcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_SEARCHBOX, m_strSearchBox);
	DDX_Control(pDX, ID_TYPE, m_cbTypeDropList);
	DDX_Control(pDX, ID_FOLDERFILEDIR, m_strPathBox);
	DDX_Control(pDX, ID_MSGBOX, m_strFoundBox);
	DDX_Control(pDX, ID_PROGCESSBAR, m_ProgcessBar);
}

BEGIN_MESSAGE_MAP(CPDFSearcherDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_PDFCHECK, &CPDFSearcherDlg::OnBnClickedPdfFormatCheck)
	ON_BN_CLICKED(ID_WORDCHECK, &CPDFSearcherDlg::OnBnClickedWordcheck)
	ON_BN_CLICKED(ID_EXCELCHECK, &CPDFSearcherDlg::OnBnClickedExcelcheck)
	ON_BN_CLICKED(ID_BTNDIR, &CPDFSearcherDlg::OnBnClickedBtnDir)
	ON_BN_CLICKED(ID_BTNSEARCH, &CPDFSearcherDlg::OnBnClickedBtnSearch)
//	ON_CBN_SELCHANGE(ID_TYPE, &CPDFSearcherDlg::OnCbnSelchangeType)
ON_CBN_SELCHANGE(ID_TYPE, &CPDFSearcherDlg::OnCbnSelchangeType)
END_MESSAGE_MAP()


// CPDFSearcherDlg message handlers

BOOL CPDFSearcherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	m_iRBFormat = 0;

	///ThinhNP - Set content for combobox 
	m_cbTypeDropList.InsertString(0, L"Folder");
	m_cbTypeDropList.InsertString(1, L"File");
	m_cbTypeDropList.SetCurSel(0);

	m_ProgcessBar.SetRange(0, 100);

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPDFSearcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPDFSearcherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPDFSearcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPDFSearcherDlg::OnBnClickedPdfFormatCheck()
{
	// TODO: Add your control notification handler code here
	m_iRBFormat = 1;
}


void CPDFSearcherDlg::OnBnClickedWordcheck()
{
	//Set value and show msg
	m_iRBFormat = 2;
}


void CPDFSearcherDlg::OnBnClickedExcelcheck()
{
	//Set value and show msg
	m_iRBFormat = 3;
}


void CPDFSearcherDlg::OnBnClickedBtnDir()
{
	//Check if combobox Type choose
	if (m_cbTypeDropList.GetCurSel() == 0)
	{
		CFolderPickerDialog dlg(FALSE);
		CString strFolderName;

		if (dlg.DoModal() == IDOK)
		{
			strFolderName = dlg.GetPathName();
		}
		m_strPathBox.SetWindowTextW(strFolderName);
	}
	else
	{
		CFileDialog dlg(TRUE);
		CString strFolderName;

		if (dlg.DoModal() == IDOK)
		{
			strFolderName = dlg.GetPathName();
		}
		m_strPathBox.SetWindowTextW(strFolderName);
	}
}

//When press Search BTN
void CPDFSearcherDlg::OnBnClickedBtnSearch()
{
	//Check if search box is empty
	CString str_Search;
	m_strSearchBox.GetWindowTextW(str_Search);
	if (str_Search.IsEmpty())
	{
		MessageBox(_T("Search data is empty, please type what you want to search into KEYWORD TO SEARCH box."), _T("KEYWORD TO SEARCH"), MB_ICONWARNING);
		return;
	}

	//Check if radio button is not check
	if (m_iRBFormat == 2 || m_iRBFormat == 3)
	{
		MessageBox(_T("This mode is not ready, please contact your developer for more information."), _T("Mode Search"), MB_ICONWARNING);
		return;
	}
	else if (m_iRBFormat == 0)
	{
		MessageBox(_T("Please choose format to search in MODE box."), _T("Mode Search"), MB_ICONWARNING);
		return;
	}

	//Check if folder path or file is empty
	CString str_Path;
	m_strPathBox.GetWindowTextW(str_Path);
	if (str_Path.IsEmpty() && m_cbTypeDropList.GetCurSel() == 0)
	{
		MessageBox(_T("Please choose the folder you want to search."), _T("WHERE TO FIND"), MB_ICONWARNING);
		return;
	}
	else if (str_Path.IsEmpty() && m_cbTypeDropList.GetCurSel() == 1)
	{
		MessageBox(_T("Please choose the file you want to search."), _T("WHERE TO FIND"), MB_ICONWARNING);
		return;
	}

	std::string strDirectory(CW2A(str_Path.GetString()));
	vt_strUnFiltFileName.clear();
	GetFilesNameInDir(strDirectory, vt_strUnFiltFileName);
	
}

void CPDFSearcherDlg::GetFilesNameInDir(const std::string& dir, strFilesName& v)
{
	std::filesystem::path p(dir);
	std::filesystem::directory_iterator start(p);
	std::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), path_leaf_string());
}


void CPDFSearcherDlg::OnCbnSelchangeType()
{
	// TODO: Add your control notification handler code here
	m_strPathBox.SetWindowTextW(L"");
}

int CPDFSearcherDlg::FuncForFun(std::string path, std::string keyword)
{
	int ret = 0;
	PDFNet::Initialize(LicenseKey);

	try
	{
		PDFDoc doc(path);
		doc.InitSecurityHandler();

		TextSearch txt_search;
		TextSearch::Mode mode = TextSearch::e_whole_word | TextSearch::e_page_stop;
		UString pattern(keyword);

		//call Begin() method to initialize the text search.
		txt_search.Begin(doc, pattern, mode);

		int step = 0;

		//call Run() method iteratively to find all matching instances.
		while (true)
		{
			SearchResult result = txt_search.Run();

			if (result.GetMatch() == keyword)
			{	//Found the keyword!!!

			}
			else
			{
				assert(result.IsDocEnd());
				break;
			}
		}
	}
	catch (Exception& e)
	{
		//Error Exception
		ret = 1;
	}
	catch (...)
	{
		//"Unknown Exception"
		ret = 2;
	}

	PDFNet::Terminate();
	return ret;
}

void CPDFSearcherDlg::FilterPDFFromList(strFilesName& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::string format = v[i].substr(v[i].length() - 4, v[i].length());
		if (format == ".pdf")
		{
			vt_strPDF.push_back(v[i]);
		}
	}
}