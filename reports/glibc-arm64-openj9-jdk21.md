---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 10:08:24 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 9 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1790690617 46
1790690622 46
1790690627 46
1790690632 46
1790690637 46
1790690642 46
1790690647 46
1790690652 46
1790690657 46
1790690662 46
1790690667 46
1790690672 46
1790690677 46
1790690682 46
1790690687 41
1790690692 41
1790690697 41
1790690702 41
1790690707 41
1790690712 41
```
</details>

---

