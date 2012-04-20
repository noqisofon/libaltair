#ifndef altair_transplant_h
#define altair_transplant_h


/**
 * \def LT_NEAR_COMPLETE_TRANSPLANT_RATE
 * 完全に近い移植率を表します。
 * <p>
 * Smalltalk に近い移植率を達成することはまず無理なので、ALTAIR_TRANSPLANTLY がこの値になることはまずありません。
 * 今はそこまで実装することもないと思います。
 * </p>
 */
#define    LT_NEAR_COMPLETE_TRANSPLANT_RATE       10000
/**
 * \def LT_STANDARD_TRANSPLANT_RATE
 * 標準の移植率を表します。
 * <p>
 * 簡単なリフレクションやシリアライズなどが可能です。
 * </p>
 */
#define    LT_STANDARD_TRANSPLANT_RATE             5000
/**
 * \def LT_MINIMUM_TRANSPLANT_RATE
 * 必要最低限の移植率を表します。
 * <p>
 * メソッドを数え上げるなどのリフレクションや、関数にブロックを渡すなどといったことはできません。
 * また、定義されたメソッドの数も少なめです。
 * </p>
 */
#define    LT_MINIMUM_TRANSPLANT_RATE              1000


#endif  /* altair_transplant_h */
