---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795613522 33
1795613527 33
1795613532 33
1795613537 33
1795613542 33
1795613547 33
1795613552 33
1795613557 64
1795613562 64
1795613567 33
1795613572 33
1795613577 33
1795613582 33
1795613587 33
1795613592 33
1795613597 33
1795613602 33
1795613607 33
1795613612 33
1795613617 33
```
</details>

---

