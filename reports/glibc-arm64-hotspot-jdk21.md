---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 10:44:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794411644 48
1794411649 48
1794411654 48
1794411659 48
1794411664 48
1794411669 48
1794411674 48
1794411679 48
1794411684 48
1794411689 48
1794411694 48
1794411699 48
1794411704 48
1794411709 28
1794411714 28
1794411719 28
1794411724 28
1794411729 28
1794411734 28
1794411739 28
```
</details>

---

