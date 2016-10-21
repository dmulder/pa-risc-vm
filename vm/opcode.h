// OPCODES
#define BREAK       0 // ['BREAK', 'RFI', 'RFIR', 'SSM', 'RSM', 'MTSM', 'LDSID', 'MTSP', 'MTCTL', 'MFSP', 'MFCTL', 'SYNC', 'SYNCDMA']
#define PROBE       1 // ['PROBER', 'PROBERI', 'PROBEW', 'PROBEWI', 'LPA,cmplt', 'LCI', 'PDTLB,cmplt', 'PITLB,cmplt', 'PDTLBE,cmplt', 'PITLBE,cmplt', 'IDTLBA', 'IITLBA', 'IDTLBP', 'IITLBP', 'PDC,cmplt', 'FDC,cmplt', 'FIC,cmplt', 'FDCE,cmplt', 'FICE,cmplt']
#define ADD         2 // ['ADD,cond', 'ADDL,cond', 'ADDO,cond', 'ADDC,cond', 'ADDCO,cond', 'SH1ADD,cond', 'SH1ADDL,cond', 'SH1ADDO,cond', 'SH2ADD,cond', 'SH2ADDL,cond', 'SH2ADDO,cond', 'SH3ADD,cond', 'SH3ADDL,cond', 'SH3ADDO,cond', 'SUB,cond', 'SUBO,cond', 'SUBB,cond', 'SUBBO,cond', 'SUBT,cond', 'SUBTO,cond', 'DS,cond', 'COMCLR,cond', 'OR,cond', 'XOR,cond', 'AND,cond', 'ANDCM,cond', 'UXOR,cond', 'UADDCM,cond', 'UADDCMT,cond', 'DCOR,cond', 'IDCOR,cond']
#define LDST        3 // ['LDWX,cmplt,cc', 'LDHX,cmplt,cc', 'LDBX,cmplt,cc', 'LDWAX,cmplt,cc', 'LDCWX,cmplt,cc', 'LDWS,cmplt,cc', 'LDHS,cmplt,cc', 'LDBS,cmplt,cc', 'LDWAS,cmplt,cc', 'LDCWS,cmplt,cc', 'STWS,cmplt,cc', 'STHS,cmplt,cc', 'STBS,cmplt,cc', 'STWAS,cmplt,cc', 'STBYS,cmplt,cc']
#define _DEBUG       4 // ['DEBUGID', 'MFDBAM', 'MFDBAO', 'MFIBAM', 'MFIBAO', 'MTDBAM', 'MTDBAO', 'MTIBAM', 'MTIBAO']
#define DIAG        5
#define FMPYADD     6
#define LDIL        8
#define WXWF        9 // ['CLDWX,uid,cmplt,cc', 'CSTWX,uid,cmplt,cc', 'CLDWS,uid,cmplt,cc', 'CSTWS,uid,cmplt,cc', 'FLDWX,cmplt,cc', 'FSTWX,cmplt,cc', 'FLDWS,cmplt,cc', 'FSTWS,cmplt,cc']
#define ADDIL       10
#define DXDS        11 // ['CLDDX,uid,cmplt,cc', 'CSTDX,uid,cmplt,cc', 'CLDDS,uid,cmplt,cc', 'CSTDS,uid,cmplt,cc', 'FLDDX,cmplt,cc', 'FSTDX,cmplt,cc', 'FLDDS,cmplt,cc', 'FSTDS,cmplt,cc']
#define FTEST       12 // ['COPR,uid,sop,n', 'FTEST,cond', 'PMENB', 'PMDIS,n']
#define LDO         13
#define FC          14 // ['FCNVFF,sf,df', 'FCNVXF,sf,df', 'FCNVFX,sf,df', 'FCNVFXT,sf,df', 'FCPY,fmt', 'FABS,fmt', 'FSQRT,fmt', 'FRND,fmt', 'FADD,fmt', 'FSUB,fmt', 'FMPY,fmt', 'FDIV,fmt', 'XMPYU', 'FCMP,fmt,cond']
#define LDB         16
#define LDH         17
#define LDW         18
#define LDWM        19
#define STB         24
#define STH         25
#define STW         26
#define STWM        27
#define COMBT       32
#define COMIBT      33
#define COMBF       34
#define COMIBF      35
#define COMICLR     36
#define SUBI        37
#define FMPYSUB     38
#define ADDBT       40
#define ADDIBT      41
#define ADDBF       42
#define ADDIBF      43
#define ADDIT       44
#define ADDI        45
#define BVB         48
#define BB          49
#define MOVB        50
#define MOVIB       51
#define EXTR        52 // ['VSHD,cond', 'SHD,cond', 'VEXTRU,cond', 'VEXTRS,cond', 'EXTRU,cond', 'EXTRS,cond']
#define DEP         53
#define BE          56
#define BLE         57
#define CALL        58 // ['BL,n', 'GATE,n', 'BLR,n', 'BV,n']
