# DataTable Mirror

An Unreal Engine editor plugin that automatically exports DataTable assets to JSON on save. Includes a commandlet for CI/CD pipelines.

## Features

- **Auto-export on save** — Every time you save a DataTable in the editor, a corresponding `.json` mirror file is written to disk.
- **Configurable output directory** — Set via Project Settings > Plugins > DataTable Mirror (default: `Data/JSON/`).
- **Console command** — `DataTableMirror.GenerateMissingJson` scans all DataTables and generates missing JSON files.
- **Headless commandlet** — `DataTableMirrorCommandlet` for CI/CD pipelines.

## Installation

Clone or copy this repo into your project's `Plugins/` directory:

```bash
git clone https://github.com/YOUR_USER/DataTableMirror.git YourProject/Plugins/DataTableMirror
```

Or add as a submodule:

```bash
git submodule add https://github.com/YOUR_USER/DataTableMirror.git Plugins/DataTableMirror
```

Regenerate project files and rebuild.

## Usage

### Editor — Auto-export

Save any DataTable asset — the JSON mirror is written automatically.

### Console command

Open the editor console (~) and run:

```
DataTableMirror.GenerateMissingJson
```

### CI/CD — Commandlet

```batch
UnrealEditor-Cmd.exe YourProject.uproject -Run=DataTableMirrorCommandlet
```

### Configuration

Edit > Project Settings > Plugins > DataTable Mirror

| Setting | Default | Description |
|---|---|---|
| OutputDirectory | `Data/JSON` | Directory relative to project root |
| bAutoExportOnSave | true | Enable/disable auto-export on save |

## Output format

```json
[
  {
    "Name": "RowName1",
    "FieldA": "value",
    "FieldB": 42
  },
  {
    "Name": "RowName2",
    "FieldA": "other",
    "FieldB": 99
  }
]
```

## Requirements

- Unreal Engine 5.4+
- Editor module (not available in runtime builds)

## License

MIT
