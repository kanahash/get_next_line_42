/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_explanation.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:47:01 by kanahash          #+#    #+#             */
/*   Updated: 2025/01/08 05:48:08 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * ft_strjoin:
 *   - 2つの文字列 s1 と s2 を連結し、"新しい文字列"を作って返す関数です。
 *   - 戻り値として、malloc( ) で確保した領域へのポインタを返すので、
 *     呼び出し元は使い終わったら free( ) する必要があります。
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t len1;      // s1 の長さ
	size_t len2;      // s2 の長さ
	size_t total_len; // s1 + s2 + 終端文字('\0')の合計長
	char *strage;     // 結果を格納するための領域(ヒープ領域)
	// s1 と s2 の長さを取得
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	// 結合後の文字列長は (s1 の長さ + s2 の長さ + 1)
	total_len = len1 + len2 + 1;
	// total_len 分のメモリを確保 (キャストは好みですが、C++互換を考慮している場合などに使われます)
	strage = (char *)malloc(total_len);
	if (!strage)
		return (NULL); // メモリ確保失敗 → NULL を返す
	// まず最初の文字を入れておかないと、strage の中身が不定なので安全のため空文字にする
	strage[0] = '\0';
	// strage に s1 をコピーし、そのあと s2 をコピー
	// ft_strlcat を利用して安全にコピーします
	ft_strlcat(strage, s1, total_len);
	ft_strlcat(strage, s2, total_len);
	// 最後に新しく作った連結文字列を返す
	return (strage);
}

/*
 * ft_strlcat:
 *   - 文字列の末尾に、別の文字列をサイズ制限つきで連結する関数です。
 *   - 'dest' の長さをまず調べ、その後ろに 'src' をコピーしていきます。
 *   - 'size' は 'dest' バッファ全体のサイズ。オーバーランしないように注意してコピーします。
 *   - 結果として、(もともとの dest 長 + src 長) を返しますが、
 *     'size' を越えるような連結はせず、安全に終端文字('\0')をつける実装になっています。
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dest_len; // dest の長さ (ただし size より大きくならない範囲)
	size_t src_len;  // src の長さ
	size_t i;        // コピー用のインデックス
	dest_len = 0;
	src_len = 0;
	i = 0;
	// まず dest の長さを数える
	// ただし 'size' を超えないようにしながら '\0' が出るまで進める
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	// src の長さを数える(こちらは '\0' まで全部調べる)
	while (src[src_len] != '\0')
		src_len++;
	// もしすでに dest_len が size 以上なら、dest に空きはない状態
	// → 結果として (size + src_len) を返す仕様
	//   (コピーはしない)
	if (dest_len >= size)
		return (size + src_len);
	// src の文字を dest にコピーしていく
	// (dest_len + i + 1 < size) → 終端文字分も確保しながらコピー
	while ((src[i] != '\0') && (dest_len + i + 1 < size))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	// コピーが終わった位置に '\0' を付与する
	dest[dest_len + i] = '\0';
	// 実際にできあがった連結文字列の長さは "dest_len + src_len"
	// (ただし、size を超えてコピーしないようにしている)
	return (dest_len + src_len);
}

/*
 * ft_strlen:
 *   - C文字列の長さ(終端文字 '\0' までの文字数)を返す関数です。
 */
int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	// '\0' が見つかるまで len をカウントアップ
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
