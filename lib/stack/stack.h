#ifndef ___Stack
#define ___Stack

typedef struct
{
    /// @brief 容量
    int capacity;
    /// @brief データの個数(正確には頂上の値が何番目か)
    int size;
    /// @brief Stackを表す配列の先頭要素へのポインタ
    int *array;
} stack;

/// @brief 初期化する関数
/// @param s スタックのポインタ
/// @param size スタックのサイズ
/// @return 正常終了時は0、メモリ確保に失敗した時は-1
int initialize(stack *s, int size);

/// @brief 要素を追加する関数
/// @param s スタックのポインタ
/// @param value 追加する要素
/// @return 正常終了時は0、スタックの容量が不足している時は-1
int push(stack *s, int value);

/// @brief 頂上の要素を削除する関数
/// @param s スタックのポインタ
/// @param top 取り出した要素
/// @return 正常終了時は0、スタックの要素数が0以下の時は-1
int pop(stack *s, int *top);

/// @brief 頂上の値を取得する関数
/// @param s スタックのポインタ
/// @param top 両城の値
/// @return 正常終了時は0、スタックの要素数が0以下の時は-1
int peek(stack *s, int *top);

/// @brief データを全て削除する関数
/// @param s スタックのポインタ
/// @return 
void clear(stack *s);

/// @brief 容量を取得する関数
/// @param s スタックのポインタ
/// @return 容量
int capacity(const stack *s);

/// @brief 積まれているデータ数を取得する関数
/// @param s スタックのポインタ
/// @return データ数
int size(const stack *s);

/// @brief スタックが空か取得する関数
/// @param s スタックのポインタ
/// @return 空ではない時は0、空の時は1
int is_empty(const stack *s);

/// @brief スタックが満杯か取得する関数
/// @param s スタックのポインタ
/// @return 満杯ではない時は0、満杯の時は1
int is_full(const stack *s);

#endif