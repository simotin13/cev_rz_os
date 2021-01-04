#include <stdint.h>
#define PAGE_TABLE_LOCATION         (0x20000000)    // ページテーブル配置アドレス(CEV-RZ/A1L 内蔵RAM先頭)
#define SECTION_ENTRY_SIZE          (4096)          // セクションエントリ数 4096
#define SCTION_SIZE                 (0x100000)      // セクション領域サイズ 1MB
#define SECTION_BIT_OFFSET_B        (2)             // B:2
#define SECTION_BIT_OFFSET_C        (3)             // C:3
#define SECTION_BIT_OFFSET_XN       (4)             // XN:4
#define SECTION_BIT_OFFSET_DOMAIN   (5)             // ドメイン[8:5]
#define SECTION_BIT_OFFSET_AP0_1    (10)            // AP1-0[11:10]
#define SECTION_BIT_OFFSET_TEX      (12)            // TEX[14:12]
#define SECTION_BIT_OFFSET_AP2      (15)            // AP2:15
#define SECTION_BIT_OFFSET_S        (16)            // S
#define SECTION_BIT_OFFSET_nG       (17)            // nG
#define SECTION_BIT_OFFSET_NS       (19)            // NS

// ============================================================================
// AP アクセス許可設定
// ============================================================================
#define AP_BOTH_DISABLE             (0x00)          // アクセス許可設定 特権:アクセス禁止   ユーザ:アクセス禁止
#define AP_SU_RW_U_DISABLE          (0x01)          // アクセス許可設定 特権:Read/Write     ユーザ:アクセス禁止
#define AP_SU_RW_U_RO               (0x02)          // アクセス許可設定 特権:Read/Write     ユーザ:Read
#define AP_BOTH_RW                  (0x03)          // アクセス許可設定 特権:Read/Write     ユーザ:Read/Write
#define AP_SU_R_U_DISABLE           (0x05)          // アクセス許可設定 特権:Read           ユーザ:アクセス禁止
#define AP_BOTH_R                   (0x06)          // アクセス許可設定 特権:Read           ユーザ:Read


void initialize_page_table(uint32_t* pTable)
{
    int i;
    uint32_t entry;
    uint32_t addr = 0;
    for (i = 0; i < SECTION_ENTRY_SIZE; i++) {
        entry = 0;

        // ================================================
        // ベースアドレスの設定 物理アドレスと一致
        // ================================================
        entry |= addr;                      // ベースアドレスの設定[31:20]
        addr += SCTION_SIZE;                // 次のアドレスを計算

        // ================================================
        // NSビットの設定  0:セキュア
        // ================================================
        entry |= (0UL << SECTION_BIT_OFFSET_NS);

        // ================================================
        // nGビットの設定 0:グローバル
        // ================================================
        entry |= (0x00UL << SECTION_BIT_OFFSET_nG);

        // ================================================
        // Sビットの設定 0:共有不可
        // ================================================
        entry |= (0x00UL << SECTION_BIT_OFFSET_S);

        // ================================================
        // APビットの設定 特権ユーザのみ
        // ================================================
        entry |= (AP_SU_RW_U_DISABLE & 0x04UL) << SECTION_BIT_OFFSET_AP2;
        entry |= (AP_SU_RW_U_DISABLE & 0x03UL) << SECTION_BIT_OFFSET_AP0_1;

        // ================================================
        // TEX,C,Bビットの設定 TEX:010 C:0 B:0 共有不可デバイス
        // ================================================
        entry |= (0x02UL << SECTION_BIT_OFFSET_TEX);

        // ================================================
        // ドメイン設定 ドメイン:0(未使用)
        // ================================================
        // Skip

        // ================================================
        // XN 実行許可 許可:0
        // ================================================
        // Skip

        // ================================================
        // bit0～bit1 bit1:1 bit0:0
        // ================================================
        entry |= 0x02;
        pTable[i] = entry;    // テーブルのエントリに値を設定
    }
}
