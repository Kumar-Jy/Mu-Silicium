# Exact remtrik v2611.21 DSDT for nabu

Current `main` moved ACPI packaging from `Include/ACPI.inc` to
`Silicium-ACPI/.../nabu/AcpiTables.inf` and its submodule DSDT is still the
newer table (`390074` bytes, SHA-256 `8b5e8b75…`) that caused the Windows
`ACPI BIOS Error`. This directory overrides only the DSDT with the exact blob
from the official remtrik v2611.21 release.

Source:
https://github.com/remtrik-stuff/MiPad5-Windows-Releases/releases/tag/2611.21

Release assets (SHA-256):
- `XiaomiPad5.UEFI-v2611.21.img`:
  `bad34edf94e5c44da3bdd7d700a9287b99ddd10e8b7def8bacd072409140fd42`
- `XiaomiPad5.UEFI-v2611.21_nSB.img`:
  `0811513baae4d6ac7775897b2b5cf4baa026562e2b604378f482fd7a6a1ae114`

The Android bootimg `kernel` payload is gzip-compressed. Its decompressed
firmware volume contains the embedded tables used here.

Active override:
- `DSDT.aml` (324801 bytes):
  `02babbe97ef69806bbf8bf3a3ba45467f5a0b7c57a3d2f96ccbafb46159f552c`

The upstream `Silicium-ACPI` submodule on current `main` already contains the
correct APIC table (`69633f9d…`), so `AcpiTables.inf` continues to use
`Hana/APIC.aml` from the submodule. The exact APIC blob is kept here only for
reference.

Archived DSDT variants, kept for reference:
- `DSDT_20260823.aml` (324285 bytes):
  `db6c297685f45b969f5c931a34c75da00b8c7072318dfc67ee7d0bd8100997d1`
- `DSDT_20260130.aml` (324590 bytes):
  `28e7f0c6715251d874b50e8cfe79c8a56487b1ef1b416a3cb187b092989e1af6`

`Platforms/Xiaomi/nabuPkg/ACPI/nabu/AcpiTables.inf` is found through the
`Platforms/Xiaomi/nabuPkg/ACPI` entry added to `PackagesPath`, so no submodule
pointer is changed.
