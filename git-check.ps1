Write-Host "=== GIT ENV CHECK ===" -ForegroundColor Cyan

Write-Host "`n[GLOBAL USER]"
git config --global user.name
git config --global user.email

Write-Host "`n[LOCAL REPO]"
git config user.name
git config user.email

Write-Host "`n[REMOTE]"
git remote -v