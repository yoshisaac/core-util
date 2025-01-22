/* https://github.com/nir9/welcome/blob/master/lnx/very-minimal-shell/custom.ld */
SECTIONS
{
  . = 0x10000;
  ENTRY(main)
  .text : {*(.text)}
}
