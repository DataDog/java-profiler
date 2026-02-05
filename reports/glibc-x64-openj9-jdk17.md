---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-04 19:34:25 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 881 |
| Sample Rate | 14.68/sec |
| Health Score | 917% |
| Threads | 12 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 45-69 cores)</summary>

```
1770251337 45
1770251342 45
1770251347 45
1770251352 45
1770251357 45
1770251362 45
1770251367 45
1770251372 45
1770251377 45
1770251382 45
1770251387 45
1770251392 45
1770251397 45
1770251402 45
1770251407 69
1770251412 69
1770251417 69
1770251422 69
1770251427 69
1770251432 69
```
</details>

---

