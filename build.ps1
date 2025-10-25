# H.E.I.P. Build Script
# Builds the H.E.I.P. compiler and runtime

Write-Host "╔═══════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   H.E.I.P. v4.0 Build System    ║" -ForegroundColor Cyan
Write-Host "║   Dodecagramic-Overlay Compilation           ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""

# Check for MSBuild
$msbuild = & "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" -version 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ MSBuild not found. Please install Visual Studio 2019 or later." -ForegroundColor Red
 exit 1
}

Write-Host "✓ MSBuild found" -ForegroundColor Green

# Create directories
Write-Host "`nCreating build directories..." -ForegroundColor Yellow
New-Item -ItemType Directory -Force -Path "bin" | Out-Null
New-Item -ItemType Directory -Force -Path "bin\Debug" | Out-Null
New-Item -ItemType Directory -Force -Path "bin\Release" | Out-Null
New-Item -ItemType Directory -Force -Path "obj" | Out-Null
Write-Host "✓ Directories created" -ForegroundColor Green

# Build Debug
Write-Host "`nBuilding Debug configuration..." -ForegroundColor Yellow
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" `
    "HEIP_Lang_New.vcxproj" `
    /p:Configuration=Debug `
    /p:Platform=x64 `
    /verbosity:minimal

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Debug build successful" -ForegroundColor Green
} else {
 Write-Host "✗ Debug build failed" -ForegroundColor Red
exit 1
}

# Build Release
Write-Host "`nBuilding Release configuration..." -ForegroundColor Yellow
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" `
    "HEIP_Lang_New.vcxproj" `
    /p:Configuration=Release `
    /p:Platform=x64 `
    /verbosity:minimal

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Release build successful" -ForegroundColor Green
} else {
    Write-Host "✗ Release build failed" -ForegroundColor Red
    exit 1
}

Write-Host "`n╔═══════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║   Build Complete!      ║" -ForegroundColor Cyan
Write-Host "╚═══════════════════════════════════════════════════════════════╝" -ForegroundColor Cyan
Write-Host ""
Write-Host "Output binaries:" -ForegroundColor Yellow
Write-Host "  Debug:   bin\Debug\HEIP_Lang_New.exe" -ForegroundColor White
Write-Host "  Release: bin\Release\HEIP_Lang_New.exe" -ForegroundColor White
Write-Host ""
Write-Host "Try running:" -ForegroundColor Yellow
Write-Host '  .\bin\Release\HEIP_Lang_New.exe info' -ForegroundColor White
Write-Host '  .\bin\Release\HEIP_Lang_New.exe compile examples\demo.heip demo.bin' -ForegroundColor White
