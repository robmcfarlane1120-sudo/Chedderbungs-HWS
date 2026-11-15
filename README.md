# Chedderbung's HWS v1.0

A standalone Windows x64 build based on Tirlititi's Hades Workshop 0.53 (upstream commit `f428246`). It keeps HWS's FFIX editing workflow and brings the following changes into the editor.

## Appearance and navigation

- **Dark Windows UI.** Charcoal panels, gray tabs, lighter gray text inputs, and off-white text. The build uses wxWidgets 3.3.4 for Windows dark mode.
- **Larger layout.** Wider sidebar lists show more names and IDs. Larger controls and fonts make the editor easier to read at 1440p. Main tabs and script text get additional sizing.
- **Two-key list search.** Hold the first letter and tap the second to jump to matching names in single-select lists and non-editable dropdowns. For example, hold **M** and tap **E** to cycle through names beginning with **Me**. Numeric prefixes such as `0600 :` are skipped.

## Scripts and dialogue

- **Find in Script.** Use **Ctrl+F**, **F3**, and **Shift+F3** for find, next, and previous in the displayed function. Search supports case matching and wraparound.
- **Saved function labels.** Right-click a function and choose **Rename Function**. The label is stored with the project's local script data and changes how the function is displayed in the list. Script identities and game bytecode use their original identifiers.
- **Custom field text blocks.** Create an empty named block with its own ID, edit its dialogue, and assign it from the field's Text Block dropdown. HWS saves the block in the `.hws` project and exports the localized `.mes` files and Memoria `MessageFile` registrations.
- **Dialogue list actions.** **Add 10** appends blank entries in one step. **Go to End** jumps to the final entry.

## Custom fields and projects

- **Embedded field previews.** **Change Preview** embeds a selected PNG in a custom field's `.hws` project data. It follows the project when it is renamed or saved under a new filename. The preview image affects the editor display only.
- **Script-only custom field export.** With **Raw Assets** selected, **Export custom field scripts only** exports the custom field scripts and their `FieldScene` registrations while preserving existing background, walkmesh, and SPS files. The checkbox remembers its state for the current editor session.
- **Project open and save.** HWS remembers the project folder, prefills the save path for the current project, and displays the project filename and unsaved marker in the title bar.
- **Standalone executable.** The editor features above run without the external QoL companion. This build still uses Memoria for the game's mod loading.

## Building on Windows

The supported configuration for this build is **Release | x64**, with Visual Studio 2022 C++ tools, wxWidgets 3.3.4 Windows x64 headers and DLL development libraries, and Autodesk FBX SDK 2020.0.1 with its VS 2017 x64 release libraries.

From a Visual Studio developer shell:

```powershell
msbuild Hades-Workshop.vcxproj /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 '/p:WxWidgetsRoot=C:\deps\wx334' '/p:FbxSdkRoot=C:\deps\FBX'
```

The wxWidgets folder should contain `include` and `lib\vc14x_x64_dll`. The FBX folder should contain `include` and `lib\vs2017\x64\release`. Place the matching wxWidgets runtime DLLs beside the built executable to run it. This repository distributes source under the upstream GPL license. Build dependencies and game assets are obtained separately.

Based on [Tirlititi's Hades Workshop](https://github.com/Tirlititi/Hades-Workshop).
