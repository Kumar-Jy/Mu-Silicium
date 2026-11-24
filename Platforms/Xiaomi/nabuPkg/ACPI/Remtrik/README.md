# Exact remtrik v2611.21 ACPI blobs for nabu

These files are the ACPI tables from the official remtrik-stuff MiPad5 Windows
Releases `2611.21` UEFI payload, not the newer tables bundled in the
`Silicium-ACPI` submodule at commit `5a64e92`.

Source:
https://github.com/remtrik-stuff/MiPad5-Windows-Releases/releases/tag/2611.21

Release assets (SHA-256):
- `XiaomiPad5.UEFI-v2611.21.img`:
  `bad34edf94e5c44da3bdd7d700a9287b99ddd10e8b7def8bacd072409140fd42`
- `XiaomiPad5.UEFI-v2611.21_nSB.img`:
  `0811513baae4d6ac7775897b2b5cf4baa026562e2b604378f482fd7a6a1ae114`

Extraction: the Android bootimg `kernel` payload is gzip-compressed. The
decompressed firmware volume contains the ACPI tables used below.

Embedded table hashes (SHA-256):
- `APIC.aml` (748 bytes):
  `69633f9d8f32675aec2f79ac1b39d861f852697a1b866365eff576a4a2a811b4`
- `DSDT.aml` (324801 bytes):
  `02babbe97ef69806bbf8bf3a3ba45467f5a0b7c57a3d2f96ccbafb46159f552c`

The two archived DSDT variants are kept alongside the active one for reference:
- `DSDT_20260823.aml` (324285 bytes):
  `db6c297685f45b969f5c931a34c75da00b8c7072318dfc67ee7d0bd8100997d1`
- `DSDT_20260130.aml` (324590 bytes):
  `28e7f0c6715251d874b50e8cfe79c8a56487b1ef1b416a3cb187b092989e1af6`

`Platforms/Xiaomi/nabuPkg/Include/ACPI.inc` now points at `Remtrik/APIC.aml`
and `Remtrik/DSDT.aml` so the build uses these exact blobs without changing
the `Silicium-ACPI` submodule pointer.
