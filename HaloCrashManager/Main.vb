Imports System.Runtime.InteropServices
Imports System.IO
Imports HaloCrashManager.DestroyerSDK

Public Class Main

    Public Shared ProcessGame As String = "haloce.exe"

    Private Sub Main_Load(sender As Object, e As EventArgs) Handles Me.Load
       
    End Sub

#Region " Move Form "

    <DllImport("user32.DLL", EntryPoint:="ReleaseCapture")>
    Private Shared Sub ReleaseCapture()
    End Sub

    <DllImport("user32.DLL", EntryPoint:="SendMessage")>
    Private Shared Sub SendMessage(ByVal hWnd As System.IntPtr, ByVal wMsg As Integer, ByVal wParam As Integer, ByVal lParam As Integer)
    End Sub

    Private Sub Label1_MouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Label1.MouseMove
        ReleaseCapture()
        SendMessage(Me.Handle, &H112&, &HF012&, 0)
    End Sub

    Private Sub Panel1_MouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Panel1.MouseMove
        ReleaseCapture()
        SendMessage(Me.Handle, &H112&, &HF012&, 0)
    End Sub

#End Region

#Region " Loader "

    Dim Retorn As Boolean = False
    Dim Xmove As Integer = 0
    Dim Pcolor As Integer = 0
    Dim ColorRetorn As Boolean = False
    Dim ProcessNameH As String = Path.GetFileNameWithoutExtension(ProcessGame)
    Dim DLL_File As String = My.Computer.FileSystem.CurrentDirectory & "\libCrianosfera.dll"

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick

        If ColorRetorn = False Then
            Pcolor += 1
            PictureBox1.BackColor = Color.FromArgb(77, 97, Pcolor)
            If Pcolor = 255 Then
                ColorRetorn = True
            End If
        ElseIf ColorRetorn = True Then
            Pcolor -= 1
            PictureBox1.BackColor = Color.FromArgb(77, 97, Pcolor)
            If Pcolor = 0 Then
                ColorRetorn = False
            End If
        End If

        If Retorn = False Then
            Xmove += 1
            PictureBox1.Location = New Point(Xmove, 0)
            If Xmove = 400 Then
                Retorn = True
            End If
        ElseIf Retorn = True Then
            Xmove -= 1
            PictureBox1.Location = New Point(Xmove, 0)
            If Xmove = 0 Then
                Retorn = False
            End If
        End If

        Dim p As Process() = Process.GetProcessesByName(ProcessNameH)

        If p.Count = 1 Then
            CrashMonitor.Enabled = True
            Label3.Text = "Status : Starting . . ."
            If My.Computer.FileSystem.FileExists(DLL_File) = True Then
                Dim DestroyerResult As Boolean = Injector.InjectDLL(ProcessNameH, DLL_File)
                If Not DestroyerResult = True Then
                    End
                End If
                About.Close()
                Me.Hide()
                Timer1.Stop()
                Timer1.Enabled = False
            Else
                End
            End If
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        End
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        About.ShowDialog()
    End Sub

#End Region

#Region " PositionForm function "

    Function CenterForm(ByVal Form_to_Center As Form, ByVal Form_Location As Point) As Point
        Dim FormLocation As New Point
        FormLocation.X = (Me.Left + (Me.Width - Form_to_Center.Width) / 2) ' set the X coordinates.
        FormLocation.Y = (Me.Top + (Me.Height - Form_to_Center.Height) / 2) ' set the Y coordinates.
        Return FormLocation ' return the Location to the Form it was called from.
    End Function

#End Region

#Region " Anti-Crash "

    Dim Hmonitor As HaloCrashHook = New HaloCrashHook
    Dim ShowAD As Boolean = False
    Private Sub CrashMonitor_Tick(sender As Object, e As EventArgs) Handles CrashMonitor.Tick

        Dim p As Process() = Process.GetProcessesByName(ProcessNameH)
        If p.Count = 0 Then
            End
        End If

        If Hmonitor.ResultState = HaloCrashHook.ResultType.Notify Then
            If ShowAD = False Then
                Notify.ResultText = Hmonitor.ResultText
                Notify.Show()
                ShowAD = True
            End If
        ElseIf Hmonitor.ResultState = HaloCrashHook.ResultType.Indeterminate Then
            ShowAD = False
        End If
    End Sub




#End Region

   



End Class