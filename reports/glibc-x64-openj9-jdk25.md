---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 12:49:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 74-92 cores)</summary>

```
1776271492 74
1776271497 74
1776271502 79
1776271507 79
1776271512 79
1776271517 79
1776271522 79
1776271527 79
1776271532 79
1776271537 79
1776271542 79
1776271547 79
1776271552 92
1776271557 92
1776271562 92
1776271567 92
1776271572 92
1776271577 92
1776271582 92
1776271587 92
```
</details>

---

