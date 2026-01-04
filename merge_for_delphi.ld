/*
  This linker script simply merges .rdata into .data.
  The Delphi 64-bit compiler is not compatible with GCC-produced objects and produces buggy code otherwise...
*/
SECTIONS
{
  .data : { *(.rdata) }
}
