# Getting Started

## Requirements

- Unreal Engine 5.1+
- A UE project with C++ enabled (the plugin is a native code module)

## Installation

### Option A — Git clone

```bash
git clone https://github.com/DCode1119/DataTableMirror.git Plugins/DataTableMirror
```

### Option B — Git submodule

```bash
git submodule add https://github.com/DCode1119/DataTableMirror.git Plugins/DataTableMirror
```

### Option C — Manual

Download the latest release from the [Releases page](https://github.com/DCode1119/DataTableMirror/releases) and extract it into your project's `Plugins/DataTableMirror/` directory.

## Enable the plugin

1. Regenerate your project files (right-click `.uproject` → **Generate Visual Studio project files**).
2. Rebuild your project in your IDE.
3. Open your project in the Unreal Editor.
4. Navigate to **Edit > Plugins**.
5. Find **DataTable Mirror** under the **Other** category and check **Enabled**.
6. Restart the editor if prompted.

The plugin is now active. Save any DataTable asset and check the configured output directory for the JSON mirror.

## Verify it works

1. Open a DataTable asset in the editor.
2. Make a small edit and save (<kbd>Ctrl+S</kbd>).
3. Open the output directory (default: `<Project>/Data/JSON/`).
4. Confirm a `.json` file with the same name as your DataTable exists.

## Next steps

- [Usage guide](usage.md) — Auto-export, console command, commandlet details
- [CI/CD pipelines](ci-cd.md) — Automating JSON export in build pipelines
