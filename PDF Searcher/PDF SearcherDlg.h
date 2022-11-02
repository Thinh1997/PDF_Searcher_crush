
// PDF SearcherDlg.h : header file
//

#pragma once
#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/TextSearch.h>
#include <PDF/Annot.h>
#include <iostream>
#include "../LicenseKey/CPP/LicenseKey.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include <iostream>
#include <iomanip>

using namespace pdftron;
using namespace PDF;
using namespace SDF;
using namespace Common;

typedef std::vector<std::string> strFilesName;

struct t_InfoEachPDF
{
	std::string strFileName;
	std::string strFullPathName;
	std::vector<int>iPageNumb;
	bool bSearchResult;
};

struct path_leaf_string
{
	std::string operator()(const std::filesystem::directory_entry& entry) const
	{
		return entry.path().filename().string();
	}
};

//Khoi tao 1 thread ten GetPDFAndShown
UINT GetPDFAndShown(LPVOID Param);
UINT FindKeywordProcess(LPVOID Param);

// CPDFSearcherDlg dialog
class CPDFSearcherDlg : public CDialog
{
// Construction
public:
	CPDFSearcherDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PDF_SEARCHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int SearchKeywordInPDF(std::string path, std::string keyword);

private:
	afx_msg void OnBnClickedPdfFormatCheck();
	afx_msg void OnBnClickedWordcheck();
	afx_msg void OnBnClickedExcelcheck();
	afx_msg void OnBnClickedBtnDir();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnCbnSelchangeType();
	afx_msg void OnLbnSelchangeListbox();
	afx_msg void OnLbnDblclkListbox();

	void DisableAllBox();
	void CalculateProcessBar();

	CEdit m_strPathBox;
	CEdit m_strFoundBox;
	CProgressCtrl m_ProgcessBar;
	CListBox m_ListBoxResult;
	CButton m_btnSearch;
	CButton m_btnCancel;
	CEdit m_strPageNumFoundBox;
	CButton m_btnDir;
	CSpinButtonCtrl m_SpinCtrl;
	CEdit m_strPageOnPageBox;

	int m_iEachPercent;
	int m_iCurrentPercent;
	int m_iRBFormat;
	CEdit m_strSearchBox;
	CComboBox m_cbTypeDropList;
	strFilesName vt_strUnFiltFileName;
	std::vector<std::string> vt_strPDF;
	std::vector<t_InfoEachPDF> vt_PDF;

	CWinThread* thread;
	CWinThread* thread2;

public:
	time_t now;

	void ClearVtUnFiltName();
	std::string GetPathString();
	void GetFilesNameInDir(const std::string& dir, strFilesName& v);
	strFilesName* GetRawNameFilter();
	void FilterPDFFromList(strFilesName& v);
	void NumberPDFFound();
	bool CheckFolderDropList();
	void GetNameFileFromPath();
	void SetProgcessBar(int percent);
	int GetCurrentPercentProgcessBar();
	int GetPercentForEachPDF();
	void EnableAllBox();
};
