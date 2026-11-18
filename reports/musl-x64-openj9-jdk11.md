---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:00:36 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 58-84 cores)</summary>

```
1795006482 84
1795006487 84
1795006492 60
1795006497 60
1795006502 60
1795006508 60
1795006513 60
1795006518 60
1795006523 60
1795006528 60
1795006533 58
1795006538 58
1795006543 58
1795006548 58
1795006553 58
1795006558 58
1795006563 58
1795006568 58
1795006573 58
1795006578 58
```
</details>

---

