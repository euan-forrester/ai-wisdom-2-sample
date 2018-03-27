// DlgOglDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Windows.h"
#include "Mmsystem.h"
#include "time.h"
#include "DlgOgl.h"
#include "DlgOglDlg.h"
#include "CTarget.h"
#include "CMissile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// Tuning constants
//

// Initial values for the sliders
const float MissileInitialSteeringPCoefficient      = 2.0f;
const float MissileInitialSteeringICoefficient      = 0.5f;
const float MissileInitialSteeringDCoefficient      = 2.9f;
                                                    
const float MissileInitialMaxAcceleration           = 1000.0f;  // World units / second^2
const float TargetInitialMaxSpeed                   = 1250.0f;  // World units / second
                            
// Setup parameters for the sliders
const float PIDSliderRange                          = 10.0f;
const float PIDSliderIncrement                      = 0.1f;
const float PIDSliderLargeChange                    = 1.0f;
const float PIDSliderTickFrequency                  = 5.0f;
                                                    
const float MissileAccelerationSliderMinValue       = 0.0f;
const float MissileAccelerationSliderMaxValue       = 3000.0f;
const float MissileAccelerationSliderIncrement      = 50.0f;
const float MissileAccelerationSliderLargeChange    = 500.0f;
const float MissileAccelerationSliderTickFrequency  = 500.0f;

const float TargetSpeedSliderMinValue               = 0.0f;
const float TargetSpeedSliderMaxValue               = 3000.0f;
const float TargetSpeedSliderIncrement              = 50.0f;
const float TargetSpeedSliderLargeChange            = 200.0f;
const float TargetSpeedSliderTickFrequency          = 200.0f;

// Timing
const UINT  WorldUpdateFrequencyMilliseconds        = 50;
const UINT  WorldTimerIDNumber                      = 1;

const float WorldMaxTimestep                        = 0.25f; // Maximum timestep in seconds

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOglDlg dialog

CDlgOglDlg::CDlgOglDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgOglDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgOglDlg)
    m_RadioMissileControlMode   = eRADIO_MISSILE_CONTROL_PID;
    m_RadioTargetControlMode    = eRADIO_TARGET_CONTROL_AUTOMATIC;
    m_PauseWorld                = FALSE;
    m_TextBoxMissileSteeringP = _T("");
    m_TextBoxMissileSteeringI = _T("");
    m_TextBoxMissileSteeringD = _T("");
    m_TextBoxMissileAcceleration = _T("");
    m_TextBoxTargetSpeed = _T("");
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgOglDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgOglDlg)
    DDX_Radio(pDX, IDC_RADIO_MISSILE_CONTROL_PID, m_RadioMissileControlMode);
    DDX_Radio(pDX, IDC_RADIO_TARGET_CONTROL_AUTOMATIC, m_RadioTargetControlMode);
    DDX_Check(pDX, IDC_CHECK_PAUSE_WORLD, m_PauseWorld);
    DDX_Control(pDX, IDC_SLIDER_MISSILE_STEERING_P, m_SliderMissileSteeringP);
    DDX_Control(pDX, IDC_SLIDER_MISSILE_STEERING_I, m_SliderMissileSteeringI);
    DDX_Control(pDX, IDC_SLIDER_MISSILE_STEERING_D, m_SliderMissileSteeringD);
    DDX_Text(pDX, IDC_EDIT_MISSILE_STEERING_P, m_TextBoxMissileSteeringP);
    DDX_Text(pDX, IDC_EDIT_MISSILE_STEERING_I, m_TextBoxMissileSteeringI);
    DDX_Text(pDX, IDC_EDIT_MISSILE_STEERING_D, m_TextBoxMissileSteeringD);
    DDX_Text(pDX, IDC_EDIT_MISSILE_ACCELERATION, m_TextBoxMissileAcceleration);
    DDX_Text(pDX, IDC_EDIT_TARGET_SPEED, m_TextBoxTargetSpeed);
    DDX_Control(pDX, IDC_SLIDER_MISSILE_ACCELERATION, m_SliderMissileAcceleration);
    DDX_Control(pDX, IDC_SLIDER_TARGET_SPEED, m_SliderTargetSpeed);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgOglDlg, CDialog)
    //{{AFX_MSG_MAP(CDlgOglDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_RESET_SLIDERS, OnButtonResetSliders)
    ON_BN_CLICKED(IDC_BUTTON_HELP_P_COEFFICIENT, OnButtonHelpPCoefficient)
    ON_BN_CLICKED(IDC_BUTTON_HELP_I_COEFFICIENT, OnButtonHelpICoefficient)
    ON_BN_CLICKED(IDC_BUTTON_HELP_D_COEFFICIENT, OnButtonHelpDCoefficient)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOglDlg message handlers

BOOL CDlgOglDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    // TODO: Add extra initialization here

    // Seed random number generator

    srand((unsigned)time(NULL));

    // Init our keystate
    for (int i = 0; i < NUM_KEYS; i++)
    {
        m_KeyState[i] = false;
    }

    // Setup our timer
    m_Timer = SetTimer(WorldTimerIDNumber, WorldUpdateFrequencyMilliseconds, NULL);
    
    if (!m_Timer)
    {
        MessageBox("Unable to setup a system timer");
    }

    m_PreviousTime = timeGetTime();

    // Hook up our OpenGL window to our picture control
    CStatic *pclStatic = (CStatic *)GetDlgItem(IDC_OPENGLWIN);

    m_pclGlView = new CGlView(pclStatic);
    m_pclGlView->OnCreate();

    ResizeGLScene();

    // Setup our slider bars (add 0.5f to all of our floats to ensure 
    // that they get rounded properly)
    int pid_slider_max_integer                  = (int)((PIDSliderRange         / PIDSliderIncrement) + 0.5f);
    int pid_slider_increment_integer            = (int)((1.0f                   / PIDSliderIncrement) + 0.5f);
    int pid_slider_large_change_integer         = (int)((PIDSliderLargeChange   / PIDSliderIncrement) + 0.5f);
    int pid_slider_tick_frequency_integer       = (int)((PIDSliderTickFrequency / PIDSliderIncrement) + 0.5f);

    m_SliderMissileSteeringP.SetMin(-pid_slider_max_integer);
    m_SliderMissileSteeringP.SetMax(pid_slider_max_integer);
    m_SliderMissileSteeringP.SetSmallChange(pid_slider_increment_integer);
    m_SliderMissileSteeringP.SetLargeChange(pid_slider_large_change_integer);
    m_SliderMissileSteeringP.SetTickFrequency(pid_slider_tick_frequency_integer);

    m_SliderMissileSteeringI.SetMin(-pid_slider_max_integer);
    m_SliderMissileSteeringI.SetMax(pid_slider_max_integer);
    m_SliderMissileSteeringI.SetSmallChange(pid_slider_increment_integer);
    m_SliderMissileSteeringI.SetLargeChange(pid_slider_large_change_integer);
    m_SliderMissileSteeringI.SetTickFrequency(pid_slider_tick_frequency_integer);

    m_SliderMissileSteeringD.SetMin(-pid_slider_max_integer);
    m_SliderMissileSteeringD.SetMax(pid_slider_max_integer);
    m_SliderMissileSteeringD.SetSmallChange(pid_slider_increment_integer);
    m_SliderMissileSteeringD.SetLargeChange(pid_slider_large_change_integer);
    m_SliderMissileSteeringD.SetTickFrequency(pid_slider_tick_frequency_integer);

    int missile_slider_min_integer              = (int)((MissileAccelerationSliderMinValue      / MissileAccelerationSliderIncrement) + 0.5f);
    int missile_slider_max_integer              = (int)((MissileAccelerationSliderMaxValue      / MissileAccelerationSliderIncrement) + 0.5f);
    int missile_slider_increment_integer        = (int)((1.0f                                   / MissileAccelerationSliderIncrement) + 0.5f);
    int missile_slider_large_change_integer     = (int)((MissileAccelerationSliderLargeChange   / MissileAccelerationSliderIncrement) + 0.5f);
    int missile_slider_tick_frequency_integer   = (int)((MissileAccelerationSliderTickFrequency / MissileAccelerationSliderIncrement) + 0.5f);

    m_SliderMissileAcceleration.SetMin(missile_slider_min_integer);
    m_SliderMissileAcceleration.SetMax(missile_slider_max_integer);
    m_SliderMissileAcceleration.SetSmallChange(missile_slider_increment_integer);
    m_SliderMissileAcceleration.SetLargeChange(missile_slider_large_change_integer);
    m_SliderMissileAcceleration.SetTickFrequency(missile_slider_tick_frequency_integer);

    int target_slider_min_integer               = (int)((TargetSpeedSliderMinValue      / TargetSpeedSliderIncrement) + 0.5f);
    int target_slider_max_integer               = (int)((TargetSpeedSliderMaxValue      / TargetSpeedSliderIncrement) + 0.5f);
    int target_slider_increment_integer         = (int)((1.0f                           / TargetSpeedSliderIncrement) + 0.5f);
    int target_slider_large_change_integer      = (int)((TargetSpeedSliderLargeChange   / TargetSpeedSliderIncrement) + 0.5f);
    int target_slider_tick_frequency_integer    = (int)((TargetSpeedSliderTickFrequency / TargetSpeedSliderIncrement) + 0.5f);

    m_SliderTargetSpeed.SetMin(target_slider_min_integer);
    m_SliderTargetSpeed.SetMax(target_slider_max_integer);
    m_SliderTargetSpeed.SetSmallChange(target_slider_increment_integer);
    m_SliderTargetSpeed.SetLargeChange(target_slider_large_change_integer);
    m_SliderTargetSpeed.SetTickFrequency(target_slider_tick_frequency_integer);

    // Set the sliders to their initial values
    OnButtonResetSliders();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgOglDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDlgOglDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

    m_World.Draw(m_pclGlView);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgOglDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CDlgOglDlg::ResizeGLScene()
{
    RECT rect;
    GetClientRect(&rect);

    int iWidth = -(rect.right - rect.left);
    int iHeight = rect.top - rect.bottom;
    
    m_pclGlView->ReSizeGLScene(iWidth, iHeight, &m_World);
}

void CDlgOglDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);

    ResizeGLScene();

    // Force refresh
    InvalidateRect(NULL);
}

BOOL CDlgOglDlg::DestroyWindow() 
{
    delete m_pclGlView;
    
    KillTimer(m_Timer);

    return CDialog::DestroyWindow();
}

// Taken from http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winui/WinUI/WindowsUserInterface/UserInput/VirtualKeyCodes.asp
#define VK_A    0x41
#define VK_D    0x44
#define VK_W    0x57
#define VK_S    0x53

void CDlgOglDlg::ReadKeyboardState()
{
    // Only read the keyboard state if one of the windows of this application
    // has the focus
    
    if (GetFocus())
    {   
        m_KeyState[eKEY_MISSILE_THRUST]     = (GetAsyncKeyState(VK_NUMPAD8) != 0);
        m_KeyState[eKEY_MISSILE_TURN_LEFT]  = (GetAsyncKeyState(VK_NUMPAD4) != 0);
        m_KeyState[eKEY_MISSILE_TURN_RIGHT] = (GetAsyncKeyState(VK_NUMPAD6) != 0);

        m_KeyState[eKEY_TARGET_MOVE_LEFT]   = (GetAsyncKeyState(VK_A)       != 0);
        m_KeyState[eKEY_TARGET_MOVE_RIGHT]  = (GetAsyncKeyState(VK_D)       != 0);
        m_KeyState[eKEY_TARGET_MOVE_UP]     = (GetAsyncKeyState(VK_W)       != 0);
        m_KeyState[eKEY_TARGET_MOVE_DOWN]   = (GetAsyncKeyState(VK_S)       != 0);
    }
    else
    {
        for (int i = 0; i < NUM_KEYS; i++)
        {
            m_KeyState[i] = false;
        }
    }
}

void CDlgOglDlg::HandleUIControls()
{
    //
    // Set our missile and target control modes based on what the user 
    // has selected
    //

    switch (m_RadioMissileControlMode)
    {
        case eRADIO_MISSILE_CONTROL_PID:
        {
            m_World.GetMissile()->SetControlMode(eMISSILE_CONTROL_PID);

            break;
        }

        case eRADIO_MISSILE_CONTROL_KEYBOARD:
        {
            m_World.GetMissile()->SetControlMode(eMISSILE_CONTROL_KEYBOARD);

            break;
        }

        default:
        {
            TRACE("Unknown value for m_RadioMissileControlMode: %d\n", m_RadioMissileControlMode);

            break;
        }           
    }

    switch (m_RadioTargetControlMode)
    {
        case eRADIO_TARGET_CONTROL_AUTOMATIC:
        {
            m_World.GetTarget()->SetControlMode(eTARGET_CONTROL_AUTOMATIC);

            break;
        }

        case eRADIO_TARGET_CONTROL_KEYBOARD:
        {
            m_World.GetTarget()->SetControlMode(eTARGET_CONTROL_KEYBOARD);

            break;
        }

        default:
        {
            TRACE("Unknown value for m_RadioTargetControlMode: %d\n", m_RadioTargetControlMode);

            break;
        }       
    }

    //
    // Send the P, I, and D values the user has selected over to the PID controller
    //

    m_World.GetMissile()->SetSteeringPIDCoefficients(
        (float)atof(m_TextBoxMissileSteeringP), 
        (float)atof(m_TextBoxMissileSteeringI), 
        (float)atof(m_TextBoxMissileSteeringD));

    //
    // Set the missile's acceleration and the target's speed
    //

    m_World.GetMissile()->SetMaxAcceleration((float)atof(m_TextBoxMissileAcceleration));
    m_World.GetTarget()->SetMaxSpeed((float)atof(m_TextBoxTargetSpeed));
}

void CDlgOglDlg::OnTimer(UINT nIDEvent) 
{
    //
    // Begin our timestep
    //

    m_World.BeginTimestep();

    //
    // Handle keyboard input
    //

    ReadKeyboardState();

    for (int i = 0; i < NUM_KEYS; i++)
    {
        m_World.HandleKeyboardState((eKey)i, m_KeyState[i]);
    }

    //
    // Handle data entered into the controls on the dialog box
    //

    UpdateData(TRUE);

    HandleUIControls();

    //
    // Figure out how long it's been since we were called,
    // and update the world by that amount of time
    //

    DWORD current_time = timeGetTime();

    if (!m_PauseWorld)
    {
        float timestep  = (float)(current_time - m_PreviousTime) / 1000.0f;
        timestep        = min(timestep, WorldMaxTimestep);

        m_World.DoTimestep(timestep);
    }

    m_PreviousTime = current_time;

    //
    // End our timestep
    //

    m_World.EndTimestep();

    //
    // Redraw the screen
    //

    PostMessage(WM_PAINT);
    
    //
    // Call the base function
    //

    CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CDlgOglDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgOglDlg)
    ON_EVENT(CDlgOglDlg, IDC_SLIDER_MISSILE_STEERING_P, 1 /* Scroll */, OnScrollSliderMissileSteeringP, VTS_NONE)
    ON_EVENT(CDlgOglDlg, IDC_SLIDER_MISSILE_STEERING_I, 1 /* Scroll */, OnScrollSliderMissileSteeringI, VTS_NONE)
    ON_EVENT(CDlgOglDlg, IDC_SLIDER_MISSILE_STEERING_D, 1 /* Scroll */, OnScrollSliderMissileSteeringD, VTS_NONE)
    ON_EVENT(CDlgOglDlg, IDC_SLIDER_MISSILE_ACCELERATION, 1 /* Scroll */, OnScrollSliderMissileAcceleration, VTS_NONE)
    ON_EVENT(CDlgOglDlg, IDC_SLIDER_TARGET_SPEED, 1 /* Scroll */, OnScrollSliderTargetSpeed, VTS_NONE)
    //}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgOglDlg::OnScrollSliderMissileSteeringP() 
{
    CString number_format;
    number_format.LoadString(IDS_PID_TEXTBOX_NUMBER_FORMAT);

    UpdateData(TRUE);

    m_TextBoxMissileSteeringP.Format(number_format, (float)m_SliderMissileSteeringP.GetValue() * PIDSliderIncrement);

    UpdateData(FALSE);
}

void CDlgOglDlg::OnScrollSliderMissileSteeringI() 
{
    CString number_format;
    number_format.LoadString(IDS_PID_TEXTBOX_NUMBER_FORMAT);

    UpdateData(TRUE);

    m_TextBoxMissileSteeringI.Format(number_format, (float)m_SliderMissileSteeringI.GetValue() * PIDSliderIncrement);

    UpdateData(FALSE);
}

void CDlgOglDlg::OnScrollSliderMissileSteeringD() 
{
    CString number_format;
    number_format.LoadString(IDS_PID_TEXTBOX_NUMBER_FORMAT);

    UpdateData(TRUE);

    m_TextBoxMissileSteeringD.Format(number_format, (float)m_SliderMissileSteeringD.GetValue() * PIDSliderIncrement);

    UpdateData(FALSE);
}

void CDlgOglDlg::OnScrollSliderMissileAcceleration() 
{
    CString number_format;
    number_format.LoadString(IDS_ACCELERATION_SPEED_TEXTBOX_NUMBER_FORMAT);

    UpdateData(TRUE);

    m_TextBoxMissileAcceleration.Format(number_format, (float)m_SliderMissileAcceleration.GetValue() * MissileAccelerationSliderIncrement);

    UpdateData(FALSE);
}

void CDlgOglDlg::OnScrollSliderTargetSpeed() 
{
    CString number_format;
    number_format.LoadString(IDS_ACCELERATION_SPEED_TEXTBOX_NUMBER_FORMAT);

    UpdateData(TRUE);

    m_TextBoxTargetSpeed.Format(number_format, (float)m_SliderTargetSpeed.GetValue() * TargetSpeedSliderIncrement);

    UpdateData(FALSE);
}

BOOL CDlgOglDlg::PreTranslateMessage(MSG* pMsg) 
{ 
    // Ignore all keyboard messages to disable wierd beeps that are otherwise generated
    
    if ((pMsg->message >= WM_KEYFIRST) && (pMsg->message <= WM_KEYLAST))
    { 
        return TRUE; 
    } 

    return CDialog::PreTranslateMessage(pMsg); 
} 

void CDlgOglDlg::OnButtonResetSliders() 
{
    int slider_initial_value_p_integer                      = (int)((MissileInitialSteeringPCoefficient / PIDSliderIncrement)                   + 0.5f);
    int slider_initial_value_i_integer                      = (int)((MissileInitialSteeringICoefficient / PIDSliderIncrement)                   + 0.5f);
    int slider_initial_value_d_integer                      = (int)((MissileInitialSteeringDCoefficient / PIDSliderIncrement)                   + 0.5f);
    int slider_initial_value_missile_acceleration_integer   = (int)((MissileInitialMaxAcceleration      / MissileAccelerationSliderIncrement)   + 0.5f);
    int slider_initial_value_target_speed_integer           = (int)((TargetInitialMaxSpeed              / TargetSpeedSliderIncrement)           + 0.5f);
    
    m_SliderMissileSteeringP.SetValue(slider_initial_value_p_integer);
    m_SliderMissileSteeringI.SetValue(slider_initial_value_i_integer);
    m_SliderMissileSteeringD.SetValue(slider_initial_value_d_integer);
    m_SliderMissileAcceleration.SetValue(slider_initial_value_missile_acceleration_integer);
    m_SliderTargetSpeed.SetValue(slider_initial_value_target_speed_integer);

    OnScrollSliderMissileSteeringP();
    OnScrollSliderMissileSteeringI();
    OnScrollSliderMissileSteeringD();
    OnScrollSliderMissileAcceleration();
    OnScrollSliderTargetSpeed();
}

void CDlgOglDlg::OnButtonHelpPCoefficient() 
{
    DisplayHelpMessageBox(IDS_HELP_P_COEFFICIENT, IDS_HELP_P_COEFFICIENT_2);
}

void CDlgOglDlg::OnButtonHelpICoefficient() 
{
    DisplayHelpMessageBox(IDS_HELP_I_COEFFICIENT, IDS_HELP_I_COEFFICIENT_2);
}

void CDlgOglDlg::OnButtonHelpDCoefficient() 
{
    DisplayHelpMessageBox(IDS_HELP_D_COEFFICIENT, IDS_HELP_D_COEFFICIENT_2);
}

void CDlgOglDlg::DisplayHelpMessageBox(UINT help_message_id_part_1, 
                                       UINT help_message_id_part_2)
{
    CString caption;
    CString help_text_part_1;
    CString help_text_part_2;
    CString help_text_part_3;
    CString help_text_part_4;

    caption.LoadString(IDS_HELP_CAPTION);
    help_text_part_1.LoadString(help_message_id_part_1);
    help_text_part_2.LoadString(IDS_ERROR_EXPLANATION);
    help_text_part_3.LoadString(help_message_id_part_2);
    help_text_part_4.LoadString(IDS_EQUATION);

    MessageBox(help_text_part_1 + help_text_part_2 + help_text_part_3 + help_text_part_4, caption, MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
}