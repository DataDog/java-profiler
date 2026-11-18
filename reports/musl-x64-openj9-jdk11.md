---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:48:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (2 unique values: 63-69 cores)</summary>

```
1795027331 69
1795027336 69
1795027341 63
1795027346 63
1795027351 63
1795027356 63
1795027361 63
1795027366 63
1795027371 63
1795027376 63
1795027381 63
1795027386 63
1795027391 63
1795027396 63
1795027401 63
1795027406 63
1795027411 63
1795027416 63
1795027422 63
1795027427 63
```
</details>

---

