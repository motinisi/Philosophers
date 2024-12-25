## die  のデバッグ履歴

### 2024/12/25
> `86861943daf9c1d1ec552bf403df34db17630d65`

**ログ**
```bash
% ./00_test_die.sh 
0 1 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 2 is thinking
0 3 is thinking
400 1 is sleeping
400 2 has taken a fork
400 2 has taken a fork
400 2 is eating
400 3 has taken a fork
```

<br>

---

**問題 1**
- 200msの時にdieが表示されていない

<br>

---

**仮説 1**
1. `check_death`が叩かれていない
> `moniter.c:67`

<br>

---

**検証 1**

```bash
gdb --args ./philo 3 200 400 400

(gdb) break check_death
(gdb) run
```

<br>

---

**結果 1**
- 叩かれていた

<br>

---

**仮説 2**
- `monitor.c:78` の `eat_time` が `die_time` をうわまわることがない

```c
if (present_time - p_data[i].last_eat_time > p_data[i].die_time
			&& p_data->status != FIN)
```

<br>

---

**検証 2**
```bash
gdb --args ./philo 3 200 400 400

(gdb) break monitor.c:78
(gdb) run
(gdb) display present_time - p_data[i].last_eat_time
(gdb) display p_data[i].die_time
(gdb) continue
# continue は繰り返し
```

**結果 2**
```bash
(gdb) continue
Continuing.
60092 1 is sleeping
60092 3 has taken a fork
60092 3 has taken a fork
60092 3 is eating

Thread 5 "philo" hit Breakpoint 1, check_death (p_data=0x4062d0, p_num=3) at monitor.c:78
78                      if (present_time - p_data[i].last_eat_time > p_data[i].die_time
1: present_time - p_data[i].last_eat_time = -1735108299296
2: p_data[i].die_time = 200
```

**原因 2**
`present_time - p_data[i].last_eat_time = -1735108299296`

<br>

---

**調査 2**
- `present_time` の値を見る
- `p_data[i].last_eat_time` の値を見る

<br>

---
**検証**
```bash
gdb --args ./philo 3 200 400 400

(gdb) break monitor.c:78
(gdb) run
(gdb) display present_time
(gdb) display p_data[i].last_eat_time
```

**結果**
```bash
(gdb) continue
Continuing.
74409 1 is sleeping
74410 3 has taken a fork
74410 3 has taken a fork
74410 3 is eating

Thread 5 "philo" hit Breakpoint 1, check_death (p_data=0x4062d0, p_num=3) at monitor.c:78
78                      if (present_time - p_data[i].last_eat_time > p_data[i].die_time
1: present_time = 74409
2: p_data[i].last_eat_time = 1735109232368
```
> `p_data[i].last_eat_time` の値がおわってる