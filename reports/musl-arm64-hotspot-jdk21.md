---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 11:23:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 12 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778512764 64
1778512769 64
1778512774 64
1778512779 64
1778512784 64
1778512789 64
1778512794 64
1778512799 64
1778512804 64
1778512809 64
1778512814 59
1778512819 59
1778512824 59
1778512829 59
1778512834 59
1778512839 59
1778512844 59
1778512849 59
1778512854 59
1778512859 59
```
</details>

---

