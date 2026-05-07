---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:34:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 25-60 cores)</summary>

```
1778189412 29
1778189417 29
1778189422 25
1778189427 25
1778189432 25
1778189437 25
1778189442 25
1778189447 25
1778189452 25
1778189457 52
1778189462 52
1778189467 56
1778189472 56
1778189477 56
1778189482 56
1778189487 56
1778189492 56
1778189497 56
1778189502 56
1778189507 56
```
</details>

---

