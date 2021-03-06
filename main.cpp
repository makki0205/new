﻿/* -------------------------------------------------------------------------- */
/* Main.cpp																	  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							  日付		氏名			*/
/* -------------------------------------------------------------------------- */
/* 000		新規作成								2015/10/20	葛巻 大樹	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "define.h"
/* -------------------------------------------------------------------------- */
/* 定数定義																	  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* グローバル変数															   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言(private)												  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 関数名		:                                                              */
/* 機能名	    :                                                              */
/* 機能概要	   :                                                              */
/* 引数        :                   :               :                          */
/* 戻り値		:                   :               :                          */
/* 作成日		:                                                              */
/* -------------------------------------------------------------------------- */
int main ( int argc, char *argv[] )
{
    FILE         *fp;
    int           flg    = 0;
    int           index  = 0;
    int           keybaf = 0;
    int           page   = 1;
    int           moji   = 0;
    int           size   = 0;
    unsigned char inval  = 0;
    char          project[256][256];
    char          name[1024];
    char          baf[2000];
    char          inputbaf[4];
    memset( &project[0][0], 0, sizeof( project ));
    memset( &inputbaf[0], 0, sizeof( inputbaf ));
    if( argc >= 2 ) {
        index = strcmp( argv[1], "-f" );
        if( index == 0 ) {
            system( "ls ~/Desktop/backup/files > ./ls.txt" );
            flg = 1;
        } else {
            printf( "new: '%s' is not a new command.\n", argv[1] );

            return -1;
        }
    } else {
        system( "ls ~/Desktop/backup/projects > ./ls.txt" );
    }
    fp = fopen( "./ls.txt", "r" );
    if( fp == 0 ) {
        printf( "オープンエラー" );
        system( "rm -f ./ls.txt" );

        return -1;
    }
    fseek( fp, 0, SEEK_END );
    size = ftell( fp );
    fseek( fp, 0, SEEK_SET );
    fread( &baf[0], size, 1, fp );
    baf[size - 1] = '\0';
    fclose( fp );
    system( "rm -f ./ls.txt" );
    for( int i = 0 ; i < size ; i++ ) {
        if( baf[i] != '\n' ) {
            project[page][moji] = baf[i];
            moji++;
        } else {
            page++;
            moji = 0;
        }
    }
    for( int i = 1 ; i <= page ; i++ ) {
        printf( "%d: %s\n", i, &project[i][0] );
    }
    printf( "\ntemplate No.\n→" );
    scanf( "%3s", &inputbaf[0] );
    inval = atoi( &inputbaf[0] );
    if( inval == 0 || inval > page ) {
        printf( "不正な文字が含まれています" );

        return -1;
    }
    if( flg == 0 ) {
        strcpy( name, "cp -r ~/Desktop/backup/projects/" );
        strcpy( &name[strlen( &name[0] )], &project[inval][0] );
        size         = strlen( &name[0] );
        name[size++] = ' ';
        rewind( stdin );
        printf( "project Name\n→" );
        scanf( "%s", &name[size] );
    } else {
        strcpy( name, "cp -r ~/Desktop/backup/files/" );
        strcpy( &name[strlen( &name[0] )], &project[inval][0] );
        strcpy( &name[strlen( &name[0] )], " " );
        strcpy( &name[strlen( &name[0] )], &project[inval][0] );
    }
    printf( "%s\n", name );
    system( &name[0] );

    return 0;
}

/* -------------------------------------------------------------------------- */
/*              Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
