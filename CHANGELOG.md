# Changelog

## v1.0.1

- Fixed an argument count overflow in the script bytecode reader for large switches. The `.hws` format is unchanged.
- Fixed stray language tags in Single Language Mode and stopped unchanged script text from being marked as needing Parse.
- Prefilled Rename Function with the current name or alias.
- Enlarged the Function List, moved unnamed opcodes below named functions, and made the list an independent window. Right-click or press Ctrl+C to copy a zero-filled call. Double-click inserts a call on its own indented line.
- Open and Open Mod remember the last FF9 launcher and `.hws` path. Both loads require confirmation in their dialogs.
- Open Mod and Save Mod use fresh dialogs. Importing another `.hws` preserves the active project's save path, and project import reports progress.

- Added dated modification notices, clarified Tirlititi's upstream credit, and documented third-party licenses. The original GPL v3 license is unchanged.
- Fixed the Visual Studio 2022 Release x64 defaults so the project uses the v143 toolset and builds `x64/Release/HadesWorkshop.exe` inside the repository.
- Ignored local Visual Studio cache files, publish output folders, and the publish build log.
