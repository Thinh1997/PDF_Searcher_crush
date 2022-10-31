
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

using namespace pdftron;
using namespace PDF;
using namespace SDF;
using namespace Common;

typedef std::vector<std::string> strFilesName;

struct t_InfoEachPDF
{
	std::string strFileName;
	int iPageNumb;
	bool bSearchResult;
};

struct path_leaf_string
{
	std::string operator()(const std::filesystem::directory_entry& entry) const
	{
		return entry.path().filename().string();
	}
};

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
	void GetFilesNameInDir(const std::string& dir, strFilesName& v);
	int FuncForFun(std::string path, std::string keyword);

private:
	void FilterPDFFromList(strFilesName& v);

	int m_iRBFormat;
	CEdit m_strSearchBox;
	CComboBox m_cbTypeDropList;
	strFilesName vt_strUnFiltFileName;
	std::vector<std::string> vt_strPDF;
	std::vector<t_InfoEachPDF> vt_PDF;

public:
	afx_msg void OnBnClickedPdfFormatCheck();
	afx_msg void OnBnClickedWordcheck();
	afx_msg void OnBnClickedExcelcheck();
	afx_msg void OnBnClickedBtnDir();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnCbnSelchangeType();

private:
	CEdit m_strPathBox;
	CEdit m_strFoundBox;
	CProgressCtrl m_ProgcessBar;

};
