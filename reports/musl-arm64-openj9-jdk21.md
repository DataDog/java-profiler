---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 04:32:39 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1791966468 53
1791966473 53
1791966478 53
1791966483 53
1791966488 53
1791966493 53
1791966498 53
1791966503 53
1791966508 53
1791966513 53
1791966518 53
1791966523 53
1791966528 53
1791966533 53
1791966538 53
1791966543 53
1791966548 53
1791966553 53
1791966558 51
1791966563 51
```
</details>

---

