---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:02:40 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 84-89 cores)</summary>

```
1793829517 86
1793829522 86
1793829527 84
1793829532 84
1793829537 84
1793829542 84
1793829548 84
1793829553 84
1793829558 84
1793829563 84
1793829568 84
1793829573 84
1793829578 84
1793829583 89
1793829588 89
1793829593 89
1793829598 89
1793829603 89
1793829608 89
1793829613 89
```
</details>

---

