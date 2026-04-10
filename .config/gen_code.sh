#!/bin/bash
# =============================================================================
# File  : gen_code.sh
# Brief : Code-generation launcher script for My Middleware (Linux / macOS).
#
# STM32CubeMX2 calls this script when the user clicks "Generate Code".
# It delegates all heavy lifting to the "cube codegen" CLI tool.
#
# Arguments (positional, passed by CubeMX2 in this exact order):
#   $1  dfp_path           — Device Family Pack base folder ($S)
#   $2  device             — Device name ($D)
#   $3  sw_project_path    — Absolute project folder path ($P)
#   $4  cprj_file_path     — Absolute .cprj file path (#P)
#   $5  gpdsctemplateName  — GPDSC Handlebars template filename
#   $6  generatorid        — Generator ID (matches PDSC <generator id="...">)
#   $7  generatorinputfile — Generator lock-file produced by CubeMX2 ($G)
#   $8  dryRunFlag         — "--dry-run" when CubeMX2 wants GPDSC preview only
#
# Exit codes:
#   0  — success
#   1  — "cube" executable not found on PATH
#   2  — "codegen" sub-command not available in the installed cube version
# =============================================================================

# Enable debug output when the environment variable DEBUG is set.
[ -z "$DEBUG" ] || set -x

# ── Capture the directory that contains this script ──────────────────────────
shell_script_abs_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ── Map positional arguments to named variables ───────────────────────────────
dfp_path="$1"
device="$2"
sw_project_path="$3"
cprj_file_path="$4"
gpdsctemplateName="$5"
generatorid="$6"
generatorinputfile="$7"
dryRunFlag="$8"

# ── Verify that the "cube" wrapper is available on the system PATH ────────────
if ! which cube &>/dev/null; then
    echo "[GEN-ERROR] cube wrapper not found on PATH: STOP"
    exit 1
fi

# ── Verify that the "codegen" sub-command is registered ──────────────────────
if ! cube --list | grep -qi "codegen"; then
    echo "[GEN-ERROR] codegen sub-command not found: STOP"
    exit 2
fi

# ── Dry-run mode: produce only the GPDSC preview, no source files ─────────────
if [ "$dryRunFlag" = "--dry-run" ]; then
    echo "[STEP 1/1: dry-run]"
    cube codegen generategpdsc \
        --path "$generatorinputfile" \
        --generatorId "$generatorid" \
        --templatePath "$shell_script_abs_path/$gpdsctemplateName" \
        --dry-run
    exit $?
fi

# ── Normal mode: two-step generation ──────────────────────────────────────────
echo "[STEP 1/2: CODE-GEN]"
cube codegen generatefromlockfile \
    --path "$generatorinputfile" \
    --generatorId "$generatorid"

if [ $? -ne 0 ]; then
    echo "[GEN-ERROR] Code generation failed."
    exit 1
fi

echo "[STEP 2/2: GPDSC-GEN]"
cube codegen generategpdsc \
    --path "$generatorinputfile" \
    --generatorId "$generatorid" \
    --templatePath "$shell_script_abs_path/$gpdsctemplateName"
exit $?
