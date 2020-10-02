Public Class Notify

#Region " Properties "

    Private Shared _ResultText As String = String.Empty
    Public Shared Property ResultText As String
        Get
            Return _ResultText
        End Get
        Set(value As String)
            _ResultText = value
        End Set
    End Property

#End Region

    Dim GameHook As WindowHook = New WindowHook

    Private Sub Notify_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.Size = New Size(263, 97) '263, 97
        Errorlbl.Text = _ResultText
        Timer1.Enabled = True
    End Sub

    Dim FirsT As Boolean = False
    Dim CountY As Integer = 0
    Dim ShowA As Boolean = False
    Dim CountT As Integer = 0
    Dim StartCount As Boolean = False

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim GhookStatus = GameHook.ResultState
        Dim Glocation As Point = GameHook.GameLocationPoint
        Dim GSize As Size = GameHook.GameSizePoint

        If GhookStatus = WindowHook.ResultType.HookingSuccessful Then
            Dim Xp As Integer = ((Glocation.X + GSize.Width) - (Me.Size.Width + 10))
            Dim Yp As Integer = (Glocation.Y + 30)
            Me.Location = New Point(Xp, Yp)
            If FirsT = False Then
                ShowA = True
            End If
        ElseIf GhookStatus = WindowHook.ResultType.HookingError Then
            Me.Close()
        End If
        If ShowA = True Then
            If Not CountY = 97 Then
                CountY += 1
                Me.Size = New Size(263, CountY)
            Else
                StartCount = True
                ShowA = False
                CountY = 0
                FirsT = True
            End If
        End If

        If StartCount = True Then
            If Not CountT = 1000 Then
                CountT += 1
            Else
                StartCount = False
                CountT = 0
                Timer1.Enabled = False
                FirsT = False
                Me.Close()
            End If
        End If

    End Sub

#Region " No Windows Focus "

    Protected Overrides ReadOnly Property ShowWithoutActivation As Boolean
        Get
            Return True
        End Get
    End Property

    Private Const WS_EX_TOPMOST As Integer = &H8

    Private Const WS_THICKFRAME As Integer = &H40000
    Private Const WS_CHILD As Integer = &H40000000
    Private Const WS_EX_NOACTIVATE As Integer = &H8000000
    Private Const WS_EX_TOOLWINDOW As Integer = &H80

    Protected Overrides ReadOnly Property CreateParams As CreateParams
        Get
            Dim createParamsA As CreateParams = MyBase.CreateParams
            createParamsA.ExStyle = createParamsA.ExStyle Or WS_EX_TOPMOST Or WS_EX_NOACTIVATE Or WS_EX_TOOLWINDOW
            Return createParamsA
        End Get
    End Property

#End Region

End Class