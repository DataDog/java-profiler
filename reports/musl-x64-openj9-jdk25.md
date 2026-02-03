---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 04:27:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1098 |
| Sample Rate | 18.30/sec |
| Health Score | 1144% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1770110489 32
1770110494 32
1770110499 32
1770110504 32
1770110509 30
1770110514 30
1770110519 30
1770110524 30
1770110529 30
1770110534 30
1770110539 30
1770110544 30
1770110549 30
1770110554 27
1770110559 27
1770110564 27
1770110569 27
1770110574 27
1770110579 27
1770110584 27
```
</details>

---

