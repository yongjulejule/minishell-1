# minishell
42 [minishell](https://cdn.intra.42.fr/pdf/pdf/26270/en.subject.pdf) project by yongjule &amp; ghan

---

## To-do List

- [x] 팀 이름 정하기
	Fail!!
- [ ] git organization 만들기

  - [link](https://github.com/brilliantshell/minishell)

- [ ] 함수 공부

- [ ] 깃 컨벤션 - 커밋 메시지 통일

  [PREFIX] [SUFFIX] : [description]

  - prefix
    - m_ : mandatory
    - b_ : bonus
  - suffix
    - feat : 기능에 대한 설명
    - fix : 수정한 부분 
    - norm : 놂
    - etc

- [ ] 디렉토리 시스템

  - /root
    - /includes
      - 세부 디렉토리
    - /src
      - parse
      - exec
	  - redir
      - builtin

- [ ] 섹션 구분, 분업

  - [ghan](https://github.com/42ghan)
    - signal handling
    - basic terminal structure
  - [yongjule](github.com/yongjulejule)
    - execute command

---

[FlowChart](https://viewer.diagrams.net/?highlight=0000ff&edit=_blank&layers=1&nav=1&title=MiniShell#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D15pffYmkiKE5KO0HpZuSJLfFW-IhJ4zwm%26export%3Ddownload)

---

## Reference

- _[GNU Readline Library description](https://web.mit.edu/gnu/doc/html/rlman_2.html)_
- _W. Richard Stevens & Stephen A. Rago (2013). Advanced Programming in the UNIX Environment (3rd ed.) U.S. : Addison-Wesley_
- _[Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/index.html)_
- _[GNU Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)_
- _[bash source code](https://tiswww.case.edu/php/chet/bash/bashtop.html#Availability)_
- _[GNU C Library](https://www.gnu.org/software/libc/manual/html_node/index.html)_
