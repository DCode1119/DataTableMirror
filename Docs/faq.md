# FAQ

## How do I change where JSON files are saved?

Go to **Edit > Project Settings > Plugins > DataTable Mirror** and change `OutputDirectory`. The path is relative to your project root. Default: `Data/JSON`.

## Can I disable auto-export and only use the commandlet?

Yes. Set `bAutoExportOnSave` to `false` in Project Settings, then use the console command or commandlet when you need to export.

## Why JSON instead of CSV?

JSON preserves nested structs, arrays, and type information more cleanly than CSV. It's also natively supported by Unreal's `FJsonObjectConverter` and most diff tools.

## Does this work in packaged (non-editor) builds?

No. The plugin is an **Editor** module. It hooks into editor-only delegates (`OnObjectPreSave`) and uses `AssetRegistry`, which is not available in runtime builds.

## Does this support CurveTable or StringTable?

Currently, only `UDataTable` assets are exported. CurveTable and StringTable support could be added in a future release.

## The JSON file wasn't created. What should I check?

1. Verify the plugin is enabled in **Edit > Plugins**.
2. Check that `bAutoExportOnSave` is `true` in Project Settings.
3. Confirm the DataTable is not transient or a class default object (the plugin skips those).
4. Check the project's `Saved/Logs/` folder for log messages containing `DataTableMirror`.
5. Ensure the output directory path is valid and writable.

## Can I use this with source control?

Yes. That's the primary use case. The JSON mirrors provide human-readable diffs when DataTable content changes. Commit both the `.uasset` and the `.json` file.

## Is DataTable Mirror compatible with other DataTable plugins?

Generally yes. It operates on the `OnObjectPreSave` delegate and the `AssetRegistry`, which are standard engine systems. However, if another plugin modifies DataTable data during save (e.g., a custom importer), the exported JSON reflects the state after all save processors have run.

## How can I contribute?

Open an issue or pull request on [GitHub](https://github.com/DCode1119/DataTableMirror).

## How do I run the tests?

The plugin includes UE automation tests. In the editor, open **Session Frontend** (Window > Developer Tools > Session Frontend), go to the **Automation** tab, and run tests under the `DataTableMirror` category.

Tests can also be run from the command line:

```batch
UnrealEditor-Cmd.exe YourProject.uproject -Run=DataTableMirrorCommandlet -ExecCmds="Automation RunTests DataTableMirror; quit"
```
