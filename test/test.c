function! ConfigureView()
    set number
    " Р’РєР»СЋС‡РёС‚СЊ РїРѕРґСЃРІРµС‚РєСѓ СЃРёРЅС‚Р°РєСЃРёСЃР°
    syntax on
    " РџРѕРёСЃРє РїРѕ РЅР°Р±РѕСЂСѓ С‚РµРєСЃС‚Р° (РѕС‡РµРЅСЊ РїРѕР»РµР·РЅР°СЏ С„СѓРЅРєС†РёСЏ)
    set incsearch
    " РџРѕРґСЃРІРµС‡РёРІР°РЅРёРµ РїРѕРёСЃРєР°
    set hlsearch
    " СѓРјРЅР°СЏ Р·Р°РІРёСЃРёРјРѕСЃС‚СЊ РѕС‚ СЂРµРіРёСЃС‚СЂР° %)
    set ignorecase
    set smartcase
    "match errorMsg /[\t]/
    " РљРѕРґРёСЂРѕРІРєР° С‚РµРєСЃС‚Р° РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ
    set termencoding=utf8
    " Р’РєР»СЋС‡Р°РµРј РЅРµСЃРѕРІРјРµСЃС‚РёРјРѕСЃС‚СЊ РЅР°СЃС‚СЂРѕРµРє СЃ Vi (РёР±Рѕ Vi РЅР°Рј Рё РЅРµ РїРѕРЅР°РґРѕР±РёС‚СЃСЏ).
    set nocompatible
    " РџРѕРєР°Р·С‹РІР°С‚СЊ РїРѕР»РѕР¶РµРЅРёРµ РєСѓСЂСЃРѕСЂР° РІСЃС‘ РІСЂРµРјСЏ.
    set ruler
    " РџРѕРєР°Р·С‹РІР°С‚СЊ РЅРµР·Р°РІРµСЂС€С‘РЅРЅС‹Рµ РєРѕРјР°РЅРґС‹ РІ СЃС‚Р°С‚СѓСЃР±Р°СЂРµ
    set showcmd
    " Р¤РѕР»РґРёРЅРі РїРѕ РѕС‚СЃСѓРїР°Рј
    set foldenable
    set foldlevel=100
    set foldmethod=indent
    " Р’С‹РєР»СЋС‡Р°РµРј РЅР°РґРѕРµРґР»РёРІС‹Р№ "Р·РІРѕРЅРѕРє"
    set noerrorbells visualbell t_vb=
    autocmd GUIEnter * set visualbell t_vb=
    " РџРѕРґРґРµСЂР¶РєР° РјС‹С€Рё
    set mouse=a
    set mousemodel=popup
    " РќРµ РІС‹РіСЂСѓР¶Р°С‚СЊ Р±СѓС„РµСЂ, РєРѕРіРґР° РїРµСЂРµРєР»СЋС‡Р°РµРјСЃСЏ РЅР° РґСЂСѓРіРѕР№
    " Р­С‚Рѕ РїРѕР·РІРѕР»СЏРµС‚ СЂРµРґР°РєС‚РёСЂРѕРІР°С‚СЊ РЅРµСЃРєРѕР»СЊРєРѕ С„Р°Р№Р»РѕРІ РІ РѕРґРёРЅ Рё С‚РѕС‚ Р¶Рµ РјРѕРјРµРЅС‚ Р±РµР· РЅРµРѕР±С…РѕРґРёРјРѕСЃС‚Рё СЃРѕС…СЂР°РЅРµРЅРёСЏ РєР°Р¶РґС‹Р№ СЂР°Р·
    " РєРѕРіРґР° РїРµСЂРµРєР»СЋС‡Р°РµС€СЊСЃСЏ РјРµР¶РґСѓ РЅРёРјРё
    set hidden
    " РЎРєСЂС‹С‚СЊ РїР°РЅРµР»СЊ РІ gui РІРµСЂСЃРёРё РёР±Рѕ РѕРЅР° РЅРµ РЅСѓР¶РЅР°
    set guioptions-=T
    " РЎРґРµР»Р°С‚СЊ СЃС‚СЂРѕРєСѓ РєРѕРјР°РЅРґ РІС‹СЃРѕС‚РѕР№ РІ РѕРґРЅСѓ СЃС‚СЂРѕРєСѓ
    set ch=1
    " РЎРєСЂС‹РІР°С‚СЊ СѓРєР°Р·Р°С‚РµР»СЊ РјС‹С€Рё, РєРѕРіРґР° РїРµС‡Р°С‚Р°РµРј
    set mousehide
    " Р’РєР»СЋС‡РёС‚СЊ Р°РІС‚РѕРѕС‚СЃС‚СѓРїС‹
    set autoindent
    "РќРµ РїРµСЂРµРЅРѕСЃРёС‚СЊ СЃС‚СЂРѕРєРё
    set nowrap
    " РџСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёРµ РўР°Р±Р° РІ РїСЂРѕР±РµР»С‹
    set expandtab
    " Р Р°Р·РјРµСЂ С‚Р°Р±СѓР»СЏС†РёРё РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ
    set shiftwidth=4
    set softtabstop=4
    set tabstop=4
    " Р¤РѕСЂРјР°С‚ СЃС‚СЂРѕРєРё СЃРѕСЃС‚РѕСЏРЅРёСЏ
    set statusline=%<%f%h%m%r\ %b\ %{&encoding}\ 0x\ \ %l,%c%V\ %P
    set laststatus=2
    " Р’РєР»СЋС‡Р°РµРј "СѓРјРЅС‹Рµ" РѕС‚СЃС‚СѓРїС‹ ( РЅР°РїСЂРёРјРµСЂ, Р°РІС‚Рѕ РѕС‚СЃС‚СѓРї РїРѕСЃР»Рµ {)
    set smartindent
    " РћС‚РѕР±СЂР°Р¶РµРЅРёРµ РїР°СЂРЅС‹С… СЃРёРјРІРѕР»РѕРІ
    set showmatch
    set lines=50
    set columns=140
    " РќР°РІРёРіР°С†РёСЏ СЃ СѓС‡РµС‚РѕРј СЂСѓСЃСЃРєРёС… СЃРёРјРІРѕР»РѕРІ
    set iskeyword=@,48-57,_,192-255
    " РЈРґР°Р»РµРЅРёРµ СЃРёРјРІРѕР»РѕРІ Р±СЌРєСЃРїСЌР№СЃРѕРј РІ Windows
    set backspace=indent,eol,start
    set cursorline
    highlight CursorLine guibg=lightblue ctermbg=lightgray
    highlight CursorLine term=none cterm=none
    set history=200
    set wildmenu
    set list listchars=tab:в†’\ ,trail:В·
    filetype plugin on
endfunc

function! InitExternalPlugins()
    let g:UltiSnipsExpandTrigger = "<c-j>"
    let g:tagbar_left = 1
    let g:tagbar_type_rust = {
        \ 'ctagstype' : 'rust',
        \ 'kinds'     : [
            \ 'f:function',
            \ 'm:macros',
            \ 'T:types',
            \ 'm:types1',
            \ 'm:modules',
            \ 'm:consts',
            \ 'm:traits',
        \ ],
    \ }
endfunction

function! BindKeys()
    " РїСЂРѕСЃРјРѕС‚СЂ СЃРїРёСЃРєР° Р±СѓС„РµСЂРѕРІ
    nmap <C-b> <Esc>:BufExplorer<cr>
    vmap <C-b> <esc>:BufExplorer<cr>
    imap <C-b> <esc><esc>:BufExplorer<cr>
    nmap <C-\> :TagbarToggle<CR>
    cnoremap @ <c-r>=expand("%:h")<cr>/
    inoremap <Tab> <C-R>=SuperCleverTab()<cr>
    nmap <silent> <Leader>of :FSHere<cr>
    nmap fd :Rgrep<cr>
    nmap fb :GrepBuffer<cr>
    nmap p4e :!p4 edit %<cr>
endfunction

function! ConfigureCompletitions()
    " РЎР»РѕРІР° РѕС‚РєСѓРґР° Р±СѓРґРµРј Р·Р°РІРµСЂС€Р°С‚СЊ
    set complete=""
    " РР· С‚РµРєСѓС‰РµРіРѕ Р±СѓС„РµСЂР°
    set complete+=.
    " РР· СЃР»РѕРІР°СЂСЏ
    set complete+=k
    " РР· РґСЂСѓРіРёС… РѕС‚РєСЂС‹С‚С‹С… Р±СѓС„РµСЂРѕРІ
    set complete+=b
    " РёР· С‚РµРіРѕРІ
    set complete+=t

    set completeopt-=preview
    set completeopt=menuone,menu,longest,preview

    " automatically open and close the popup menu / preview window
    au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
    set mps-=[:]
endfunction

function! SuperCleverTab()
    if strpart( getline('.'), 0, col('.')-1 ) =~ '^\s*$'
        return "\<Tab>"
    else
        return "\<C-p>"
    endif
endfunction

function! LocalConf()
    if filereadable(".vim_config")
        source .vim_config
    endif
endfunc

call LocalConf()
call ConfigureView()
call BindKeys()
call ConfigureCompletitions()
call InitExternalPlugins()
