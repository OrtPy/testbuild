/* Force section boundary symbols to exist (and be exportable if needed) */
SECTIONS
{
  PROVIDE(__bss_start = .);
  PROVIDE(_edata = .);
  PROVIDE(_end = .);
}
