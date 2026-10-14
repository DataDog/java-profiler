---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 04:32:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791966458 43
1791966463 43
1791966468 43
1791966473 48
1791966478 48
1791966483 48
1791966488 48
1791966493 48
1791966499 48
1791966504 48
1791966509 48
1791966514 48
1791966519 48
1791966524 48
1791966529 48
1791966534 48
1791966539 48
1791966544 48
1791966549 48
1791966554 48
```
</details>

---

