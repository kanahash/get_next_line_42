/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_explanation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 05:44:55 by kanahash          #+#    #+#             */
/*   Updated: 2025/01/08 05:45:47 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ft_getc:
 *   - ファイルディスクリプタ fd から、1文字を取得するための関数です。
 *   - 実際にはバッファ buf にまとめ読みしておき、そこから1文字ずつ返します。
 *   - バッファが空になると再度 read( ) で読み込みます。
 */
static int	ft_getc(int fd)
{
	static unsigned char buf[BUFFER_SIZE]; // まとめ読み用のバッファ(配列)
	static unsigned char *bufp = buf;      // buf内の現在の読み込み位置を指すポインタ
	static int n = 0;                      // buf 内に残っている未読バイト数
	// バッファを使い切ったら、改めて read( ) で読み込む
	if (n == 0)
	{
		// fd から最大 BUFFER_SIZE バイトをまとめて読み込む
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0) // 読み取りエラー
			return (READ_ERROR);
		if (n == 0) // ファイルの終端 (EOF)
			return (EOF);
		bufp = buf; // バッファの先頭を指すようにリセット
	}
	// 残りバイト数を1つ減らし、その文字を返す
	if (--n >= 0)
		return (*bufp++); // bufp が指す文字を返した後、ポインタを1つ進める
	// ここに来るのはバッファを使い切ったとき（通常は上で処理されるが念のため）
	return (EOF);
}

/*
 * make_new_line:
 *   - 既存の文字列 str に、新しい1文字 c を追加した新たな文字列を作り返します。
 *   - str が NULL の場合は空文字列("")と c を連結するイメージで初期化します。
 *   - ft_strjoin( ) で動的にメモリが確保されるので、呼び出し側で free が必要。
 */
static char	*make_new_line(char *str, char c)
{
	char	*new_str;

	char temp[2]; // c を文字列として扱うための小さなバッファ
	// temp は c + 終端文字('\0') の2バイト
	temp[0] = c;
	temp[1] = '\0';
	// str が NULL なら空文字列との連結として扱う
	if (str == NULL)
		new_str = ft_strjoin("", temp);
	else
		new_str = ft_strjoin(str, temp);
	return (new_str);
}

/*
 * read_line:
 *   - ft_getc( ) で1文字ずつ取得し、行を組み立てるメイン処理です。
 *   - '\n' に当たるか、EOF( '\0' )やREAD_ERROR に当たるまで読み続けます。
 *   - 途中でメモリ確保に失敗した場合は NULL を返します。
 */
static char	*read_line(int fd)
{
	char *result;                        // 読み込み中の文字列全体を保持
	char c;                              // ft_getc( ) で取得した1文字
	char *new_line;                      // 新たな文字列を一時的に受け取るためのポインタ
	result = NULL;                       // 初期状態では文字列なし
	c = ft_getc(fd);                     // 最初の文字を取得
	while (c != '\0' && c != READ_ERROR) // EOF('\0')やエラー(READ_ERROR)でない間ループ
	{
		// 新しい文字列を生成 (既存の result に c を追加)
		new_line = make_new_line(result, c);
		if (!new_line) // メモリ確保失敗などで NULL が返ったら
		{
			free(result);  // いままでの文字列を解放して
			return (NULL); // エラー終了
		}
		// 古い文字列はもう不要なので free して
		free(result);
		// new_line を最新の文字列として result に移す
		result = new_line;
		// 改行ならループ終了 (1行読み終わり)
		if (c == '\n')
			break ;
		// 次の文字を取得してループ続行
		c = ft_getc(fd);
	}
	return (result); // 最終的に組み立てた文字列を返す (NULL の場合もありうる)
}

/*
 * get_next_line:
 *   - 実際に外部から呼び出される関数。
 *   - まず簡単なエラーチェック(fd が不正や BUFFER_SIZE が0以下 など)を行い、
 *     問題なければ read_line( ) に処理を委ねる。
 */
char	*get_next_line(int fd)
{
	// fd が負や、BUFFER_SIZE が0以下なら処理不可 → NULL を返す
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// 上記チェックを通過したら、read_line( ) で1行を読み込む
	return (read_line(fd));
}
