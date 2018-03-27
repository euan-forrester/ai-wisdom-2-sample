// DlgOglDlg.h : header file
//
//{{AFX_INCLUDES()
#include "slider.h"
//}}AFX_INCLUDES

#if !defined(AFX_DLGOGLDLG_H__358FE25E_7791_497E_8082_0F3AECB38D87__INCLUDED_)
#define AFX_DLGOGLDLG_H__358FE25E_7791_497E_8082_0F3AECB38D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlView.h"
#include "CWorld.h"

// The order here must match the order of the corresponding radio buttons 
// on the dialog box
enum eMissileControlRadioButtonValue
{
    eRADIO_MISSILE_CONTROL_PID = 0,
    eRADIO_MISSILE_CONTROL_KEYBOARD,

    NUM_RADIO_MISSILE_CONTROL_MODES,
};

// The order here must match the order of the corresponding radio buttons 
// on the dialog box
enum eTargetControlRadioButtonValue
{
    eRADIO_TARGET_CONTROL_AUTOMATIC = 0,
    eRADIO_TARGET_CONTROL_KEYBOARD,

    NUM_TARGET_CONTROL_MODES,
};

/////////////////////////////////////////////////////////////////////////////
// CDlgOglDlg dialog

class CDlgOglDlg : public CDialog
{
// Construction
public:
    CDlgOglDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgOglDlg)
    enum { IDD = IDD_DLGOGL_DIALOG };
    int     m_RadioMissileControlMode;
    int     m_RadioTargetControlMode;
    BOOL    m_PauseWorld;
    CSlider m_SliderMissileSteeringP;
    CSlider m_SliderMissileSteeringI;
    CSlider m_SliderMissileSteeringD;
    CString m_TextBoxMissileSteeringP;
    CString m_TextBoxMissileSteeringI;
    CString m_TextBoxMissileSteeringD;
    CString m_TextBoxMissileAcceleration;
    CString m_TextBoxTargetSpeed;
    CSlider m_SliderMissileAcceleration;
    CSlider m_SliderTargetSpeed;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgOglDlg)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL            PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
    void ResizeGLScene();

    HICON                   m_hIcon;
    CGlView*                m_pclGlView;
    CWorld                  m_World;

    // Generated message map functions
    //{{AFX_MSG(CDlgOglDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnScrollSliderMissileSteeringP();
    afx_msg void OnScrollSliderMissileSteeringI();
    afx_msg void OnScrollSliderMissileSteeringD();
    afx_msg void OnButtonResetSliders();
    afx_msg void OnScrollSliderMissileAcceleration();
    afx_msg void OnScrollSliderTargetSpeed();
    afx_msg void OnButtonHelpPCoefficient();
    afx_msg void OnButtonHelpICoefficient();
    afx_msg void OnButtonHelpDCoefficient();
    DECLARE_EVENTSINK_MAP()
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    void                    DisplayHelpMessageBox(UINT help_message_id_part_1, UINT help_message_id_part_2);

    void                    ReadKeyboardState();
    void                    HandleUIControls();

    UINT                    m_Timer;
    DWORD                   m_PreviousTime;

    bool                    m_KeyState[NUM_KEYS];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOGLDLG_H__358FE25E_7791_497E_8082_0F3AECB38D87__INCLUDED_)
