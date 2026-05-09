# Usage

## Auto-export on save (default)

The plugin hooks into `FCoreUObjectDelegates::OnObjectPreSave`. Every time a `UDataTable` asset is saved in the editor, the plugin serializes its rows to JSON and writes the file to the configured output directory.

### What gets exported

- All DataTable assets (`UDataTable` subclasses).
- Only non-transient, non-CDO assets.
- Each DataTable produces one JSON file named `<DataTableName>.json`.

### What does NOT trigger export

- Transient assets (runtime-only data).
- Class default objects.
- Other asset types (CurveTable, StringTable, etc.).

## Console command

The editor console (<kbd>~</kbd>) command `DataTableMirror.GenerateMissingJson` scans every DataTable in the project's asset registry and exports any that are missing their JSON mirror.

Useful when:

- You first enable the plugin in an existing project.
- The JSON directory was cleaned or reset.
- You want to bulk-export after adding new DataTables without saving each one individually.

```
DataTableMirror.GenerateMissingJson
```

## Commandlet

For headless environments (CI/CD, automation scripts), use the commandlet:

```batch
UnrealEditor-Cmd.exe YourProject.uproject -Run=DataTableMirrorCommandlet
```

See [CI/CD Integration](ci-cd.md) for detailed usage.

## Project Settings

Navigate to **Edit > Project Settings > Plugins > DataTable Mirror**.

| Setting | Default | Description |
|---|---|---|
| `OutputDirectory` | `Data/JSON` | Directory relative to `FPaths::ProjectDir()` where JSON files are written |
| `bAutoExportOnSave` | `true` | Enable or disable the automatic export on save. Disable if you only want manual/commandlet exports |

Settings are persisted in `<Project>/Config/DefaultDataTableMirror.ini`.
