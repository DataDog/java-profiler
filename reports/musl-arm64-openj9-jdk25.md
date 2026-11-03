---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:25:57 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 41-47 cores)</summary>

```
1793722742 46
1793722747 46
1793722752 46
1793722757 46
1793722762 46
1793722767 46
1793722772 46
1793722777 46
1793722782 46
1793722787 46
1793722792 47
1793722797 47
1793722802 47
1793722807 47
1793722813 46
1793722818 46
1793722823 41
1793722828 41
1793722833 41
1793722838 41
```
</details>

---

