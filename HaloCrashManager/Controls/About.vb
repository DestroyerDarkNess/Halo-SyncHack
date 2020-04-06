Public Class About

    Private Sub About_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.Location = Main.CenterForm(Me, Me.Location)
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.Close()
    End Sub

End Class