.section .text

.extern  _initialize_page_table

PAGE_TABLE_LOCATION  EQU 0x20080000 # ページテーブル配置先(内蔵RAM 大容量内蔵RAM ページ1)

LEVEL1_BASE_ADDR  EQU 0x00100000  # 第1レベルテーブルの先頭アドレス
VECTOR_BASE_ADDR  EQU 0x00000000  ; ベクタテーブル先頭アドレス

;
;  TTBCR（テーブル変換ベース制御レジスタ）/TTBR0の設定
;
MOV   r0,#0x0                ; TTBCR 0x0の初期値
MCR   p15,0,r0,c2,c0,2       ; TTBCRの書き込み
LDR   r0,=LEVEL1_BASE_ADDR   ; 第1レベルテーブルアドレスを設定
MOV   r1,#0x48               ; TTBR0の初期化を実施
                            ; TTBR0.IRGN[6.0]=01:ノーマルメモリ
                            ; 内部ライトバック書き込み割り当てキャッシュ可能
                            ; TTBR0.S[1]=0:共有不可設定
                            ; TTBR0.RGN[4:3]=01：ノーマルメモリ
                            ; 外部ライトバック・ライトアロケート・キャッシュ可能
ORR   r0,r0,r1               ; TTBR0の設定値を設定
MCR   p15,0,r0,c2,c0,0       ; TTBR0の書き込み
;
; 第1レベルテーブルの作成
;
LDR   r0,=LEVEL1_BASE_ADDR   ; 第1レベルテーブルアドレスを設定
LDR   r1,=0xfff              ; ループカウンタを初期化
LDR   r2,=0x00000de2         ; テーブルの初期設定値を設定
init_ttb_1
ORR   r3,r2,r1,LSL#20        ; ベースアドレスを設定
STR   r3,[r0,r1,LSL#2]       ; 第1記述子書き込み
SUBS  r1,r1,#1               ; ループカウンタを-1
BPL   init_ttb_1             ; 変換テーブル作成終了？
;
; ベクタ領域の第1記述子を変更
;
LDR   r1,=VECTOR_BASE_ADDR   ; ベクタの先頭アドレスを設定
LSR   r1,#20                 ; 1Mバイト境界にアドレスを設定
ORR   r3,r2,r1,LSL#20        ; テーブルの初期値を求める
ORR   r3,r3,#0x0c            ; ノーマルメモリ内部キャッシュ可能設定
ORR   r3,r3,#0x1000          ; 外部キャッシュ不可設定
STR   r3,[r0,r1,LSL#2]       ; テーブルエントリを設定
