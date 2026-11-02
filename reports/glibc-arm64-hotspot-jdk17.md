---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-01 23:46:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793594504 48
1793594509 48
1793594514 48
1793594519 48
1793594524 48
1793594529 48
1793594534 48
1793594539 48
1793594544 48
1793594549 48
1793594554 48
1793594559 48
1793594564 46
1793594569 46
1793594574 46
1793594579 46
1793594584 46
1793594589 46
1793594594 46
1793594599 46
```
</details>

---

