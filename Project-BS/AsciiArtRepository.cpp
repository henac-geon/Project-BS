﻿#include "AsciiArtRepository.h"

namespace AsciiArt {

    std::string getWelcomeArt() {
        return R"(
                          ;;
                        ;#!!:
                      ;$$!=$:
                    @@;=$@-#:
                ;*##*=##$...*== 
               ***;!$@:,.,.,-~;@**
           -;$$=====,.,.,...;$==!@:
        ~~$=!!*=**,...,...#@$=!!!@:
        @#!!!$$$..,-....:##!!!!;!@:
     !@#==@@*....-,..~@=!;!!!~..!@:
    :$==#@-..,,,,.!!#$!!!!-,;~..!@:
    ~$*=*,.,,,,.;*==!!!!--::!;~.!@:
    ~#$*=$#*::=#*!!!!~~~!!!!!!!.!@:
    :$$=!!$###;!!!;::-;!!!!!!!!.!@:
    ~*=$=*!!!$!!;.-!!!!!!!!!!!!.!@:
    ~=:!****=#=!,.-!!!!~!!!!!!!,#@;-----,-------,,-,-----..----*@=-
    ~#=:--**$$=!-;!!!!!~-!!!!!!,@######@!=#####;$@~#####$::@##$@-~$
    :#$$:,..:$=!-!!!!!-.,:!!;!!$@      @       :$@.     #*     *-~$
    :#$$**~~!$=!,!!!!!-...~~~!!$@##### @@$#### :@@. @@@@@@  @@ *-~$
    :#$$****=#=!,!!!!!-. ...!!!$@      #@      :@#. @@@@@@  #@ *-~$
    :#$$****=$=!-!!;    ...!!!!$@##### #@*.#@@@@@@      $@*    *-~$
    :#$$****=$=!,!:.  ..  ;!!!!@@##@@@#@@! ....:#@#$####@@@#..!#-~$
    :#$$****=$=!-!!;;.....-!!!!#        @#==**!=@@@@@@@@@#@@@@@@-~$
    :#$$=***=#=!-!!!!!.....!!!!@@@@-~@@@=       *        $!....:-~$
    :#$$****$#=!-!!!!,.,;-..!!!;$@@-~@#@;.......-........*=::::*-~$
    :#$$****$$=!-!!!!,.~!!, !!*;$@@,-@@@@@@@@@@@@@@@@@@@@@@@@@@@-~$
    :#$$****$$=!-!!!!,,!!!!!!!*;$@@@@#@@@@@@#@@@@@@@@@@@@#@@@@@@@##
    :#$$=***$$=!-!!!!,;!!!!!!!@##@@@@@#@@#@@@@@@@@@@@@@@@##@#@@@@@$
    :#$$****$$=!-!!!!;!!@-----@-~@@-;@~~@=-#@@*~@@@@~;#!~~~~~!@!-@$
    :#$$****$#=!,!!!!!!!@ .. .@ .@@ -@..@*.@@@;.@@#@.~@;  ...;@:.@$
    :#$$****$$=!-!!!!!!!@.;@  @ .@@  ...   @@@;.@@@@.~###~.~@**-.@$
    :*=$****$$=!-!!!!!!!@ ;@  @ .=@ -#..-,.#@@;.@@*!.~@@@~.~@. ..#$
    ~=:$****=$=!-!!!!!!!@ :@  @ ..# -#. @!.@@#;.@@...~#@#,..=#@:.@$
    :#=:,,**=$=!-!!!!!!!@ ;@  @ .$@ ....@*.@@#;.~#@@.~@*..# .:@:.@$
    :#$=..,,:#=!-!!!!!!!@ ;@  @ .@@*=**=@#=@@@-.-@@@.~##=#@@=@@!~@$
    :#$$**::!#=!-~!!!~~~@  ;  @ .@@@..@@@* @@~.~.;@@.~@@@;;;;;;;;@$
    :#$$****=$=!,.:~-!!!@     @ .@@@.. ....@=.!@-..@.~@##........@$
    ~#$$****$$=!,.-!!!!*#@@@@@@  @@@..@@@*.@#-@@@-#@.~@##.;@@@@:.@$ 
    .!@$****$$=!!!!!!!########@ .@@@.     .#@#@@@###.:@@#.  .....@$
      @@=**=$#=!!!*=@@:       @ .@@@       @@##@#@@@.~@@#........@$
       ;@##=$$=!=$=~.         ###@!@@#@####@:       @@@#~@#@##@#@@$
        =$=#@@=$
            !**,
==================================================================================================================================================================================================
          쿠르드의 마법상점에 오신 걸 환영합니다,! 

          [택스트 입력창]이 보이도록 화면을 조정해 주세요.

          >> "시작" 입력 시 게임이 시작됩니다.
)";
    }


    std::string writeBookArt() {
        return R"(
@@@@@@@@@@@@@@#@@@@@@@@@@##@@@@@@@@@@@@@
@@@@@@@@@;       ~@@@@:       ;@@@@@@@@@
@@@@@@-            @@            -@@@@@@
@!;@.              ##              .@;!@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.              ##              .@;;@
@;;@.     ,;!$#;,  ##  -;#$!;,     .@;;@
@;;@. .=@@@@@$$@@@,##,@@@$$@@@@@=. .@;;@
@;;@#@@@:~~~~~~~~=@@@@=~~~~~~~~:@@@#@;;@
@;;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;;@
@;;;!;;;;;;;;;;;;;$##$;;;;;;;;;;;;;!!;;@
@;;;!;;;;;;;;;;;;;$##$;;;;;;;;;;;;;!!;;@
     책이 성공적으로 집필되었습니다!
)";
    }


    std::string getLevelUpArt() {
        return R"(
      *     *    *
     *        *     *
    *  LEVEL UP!   *
     *     *     *
        *     *
      새로운 마법 레벨 도달!
)";
    }


    std::string getGameOverArt() {
        return R"(
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___ | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \| |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/| |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___| \____/  \_/ \___|_|   
                                                    
        게임 오버! 다시 도전하세요!
)";
    }

}
