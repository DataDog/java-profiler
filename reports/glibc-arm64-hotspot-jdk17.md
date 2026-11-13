---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:08:12 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 9 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (4 unique values: 36-43 cores)</summary>

```
1794567788 41
1794567793 41
1794567798 41
1794567803 41
1794567808 41
1794567813 41
1794567818 41
1794567823 41
1794567829 41
1794567834 36
1794567839 36
1794567844 36
1794567849 36
1794567854 38
1794567859 38
1794567864 38
1794567869 38
1794567874 43
1794567879 43
1794567884 43
```
</details>

---

