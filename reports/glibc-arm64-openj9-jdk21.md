---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 9-28 cores)</summary>

```
1790604733 9
1790604738 28
1790604743 28
1790604748 28
1790604753 28
1790604758 28
1790604763 28
1790604768 28
1790604773 28
1790604778 28
1790604783 28
1790604788 28
1790604793 28
1790604798 28
1790604803 28
1790604808 28
1790604813 28
1790604818 28
1790604823 28
1790604828 28
```
</details>

---

