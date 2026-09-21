---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 15:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 10 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790018789 48
1790018794 48
1790018799 48
1790018804 48
1790018809 48
1790018814 48
1790018819 48
1790018824 48
1790018829 48
1790018834 48
1790018839 48
1790018844 48
1790018849 48
1790018854 43
1790018859 43
1790018864 43
1790018869 43
1790018874 43
1790018879 43
1790018884 43
```
</details>

---

