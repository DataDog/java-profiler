---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 00:59:51 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 21-57 cores)</summary>

```
1790830458 21
1790830463 21
1790830468 21
1790830473 24
1790830478 24
1790830483 24
1790830488 24
1790830493 24
1790830498 24
1790830503 24
1790830508 24
1790830513 24
1790830518 24
1790830523 57
1790830528 57
1790830533 57
1790830538 57
1790830543 57
1790830548 57
1790830553 57
```
</details>

---

