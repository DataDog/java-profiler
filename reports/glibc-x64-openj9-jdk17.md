---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 17:04:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 49-70 cores)</summary>

```
1795384553 49
1795384558 49
1795384563 49
1795384568 49
1795384573 49
1795384578 49
1795384583 70
1795384588 70
1795384593 70
1795384598 70
1795384603 70
1795384608 70
1795384613 70
1795384618 70
1795384623 70
1795384628 70
1795384633 70
1795384638 70
1795384643 70
1795384648 70
```
</details>

---

