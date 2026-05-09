# CI/CD Integration

The plugin ships with `UDataTableMirrorCommandlet`, a headless commandlet class that can be run from the command line without an interactive editor session.

## Basic usage

```batch
UnrealEditor-Cmd.exe YourProject.uproject -Run=DataTableMirrorCommandlet -Log
```

The commandlet:

1. Loads the project and its plugins.
2. Scans the asset registry for all `UDataTable` assets.
3. For each DataTable that is missing its JSON mirror, calls `ExportDataTableToJson()`.
4. Logs results and exits with code `0` on success.

## Exit codes

| Code | Meaning |
|---|---|
| `0` | All DataTables processed (success, some may have been skipped if already present) |
| Non-zero | Errors during asset loading or export |

## CI pipeline examples

### GitHub Actions

```yaml
- name: Export DataTable JSON
  shell: cmd
  run: |
    "D:\Unreal\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" ^
      $(pwd)\YourProject.uproject ^
      -Run=DataTableMirrorCommandlet -Log
```

### Jenkins (Windows batch)

```batch
"%UE_ROOT%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "%WORKSPACE%\YourProject.uproject" -Run=DataTableMirrorCommandlet -Log
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%
```

### Git hooks (pre-commit)

```bash
#!/bin/bash
# .git/hooks/pre-commit
"${UE_ROOT}/Engine/Binaries/Win64/UnrealEditor-Cmd.exe" \
  "${PWD}/YourProject.uproject" \
  -Run=DataTableMirrorCommandlet -Log
```

## Checking results

The commandlet writes logs to the console. Grep for `DataTable Mirror` to find export results:

```
DataTable Mirror: JSON export complete.
```

## Automating before commits

Run the commandlet before committing DataTable changes to ensure the JSON mirrors are always in sync:

```batch
UnrealEditor-Cmd.exe YourProject.uproject -Run=DataTableMirrorCommandlet -Log
git add Data/JSON/
git commit -m "Update DataTable JSON mirrors"
```
