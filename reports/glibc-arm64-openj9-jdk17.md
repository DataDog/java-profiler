---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 04:32:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1791966443 38
1791966448 38
1791966453 38
1791966458 43
1791966463 43
1791966468 43
1791966473 43
1791966478 43
1791966483 43
1791966488 43
1791966493 43
1791966498 43
1791966503 43
1791966508 43
1791966513 43
1791966518 43
1791966523 43
1791966528 43
1791966533 43
1791966538 43
```
</details>

---

