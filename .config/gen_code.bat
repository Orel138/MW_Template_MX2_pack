@echo off
GOTO :END_COMMENT
/**
  * @file   gen_code.bat
  * @brief  Code-generation launcher script for My Middleware (Windows).
  *
  * STM32CubeMX2 calls this script when the user clicks "Generate Code".
  * It delegates all heavy lifting to the "cube codegen" CLI tool.
  *
  * Arguments (positional, passed by CubeMX2 in this exact order):
  *   %1  dfp_path          — Device Family Pack base folder ($S)
  *   %2  device            — Device name ($D)
  *   %3  sw_project_path   — Absolute project folder path ($P)
  *   %4  cprj_file_path    — Absolute .cprj file path (#P)
  *   %5  gpdsctemplateName — GPDSC Handlebars template filename
  *   %6  generatorid       — Generator ID (matches PDSC <generator id="...">)
  *   %7  generatorinputfile— Generator lock-file produced by CubeMX2 ($G)
  *   %8  dryRunFlag        — "--dry-run" when CubeMX2 wants GPDSC preview only
  *
  * Exit codes:
  *   0  — success
  *   1  — "cube" executable not found on PATH
  *   2  — "codegen" sub-command not available in the installed cube version
  */
:END_COMMENT

REM ── Capture the directory that contains this script ──────────────────────────
set "script_path=%~dp0"

REM ── Map positional arguments to named variables ───────────────────────────────
set "dfp_path=%1"
set "device=%2"
set "sw_project_path=%3"
set "cprj_file_path=%4"
set "gpdsctemplateName=%5"
set "generatorid=%6"
set "generatorinputfile=%7"
set "dryRunFlag=%8"

REM ── Verify that the "cube" wrapper is available on the system PATH ────────────
where cube >nul 2>nul
if %errorlevel% neq 0 (
    echo [GEN-ERROR] cube wrapper not found on PATH: STOP
    exit /b 1
)

REM ── Verify that the "codegen" sub-command is registered ──────────────────────
cube --list | findstr /i "codegen" >nul
if %errorlevel% neq 0 (
    echo [GEN-ERROR] codegen sub-command not found: STOP
    exit /b 2
)

REM ── Dry-run mode: produce only the GPDSC preview, no source files ─────────────
if "%dryRunFlag%"=="--dry-run" (
    cube codegen generategpdsc ^
        --path %generatorinputfile% ^
        --generatorId "%generatorid%" ^
        --templatePath "%script_path%\%gpdsctemplateName%" ^
        --dry-run
    exit /b %errorlevel%
)

REM ── Normal mode: two-step generation ──────────────────────────────────────────
echo [STEP 1/2: CODE-GEN]
cube codegen generatefromlockfile ^
    --path %generatorinputfile% ^
    --generatorId "%generatorid%"
if %errorlevel% neq 0 (
    echo [GEN-ERROR] Code generation failed.
    exit /b %errorlevel%
)

echo [STEP 2/2: GPDSC-GEN]
cube codegen generategpdsc ^
    --path %generatorinputfile% ^
    --generatorId "%generatorid%" ^
    --templatePath "%script_path%\%gpdsctemplateName%"
exit /b %errorlevel%
