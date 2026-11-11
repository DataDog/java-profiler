---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 04:41:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 9 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 39-44 cores)</summary>

```
1794389830 44
1794389835 44
1794389840 44
1794389845 44
1794389851 44
1794389856 44
1794389861 44
1794389866 44
1794389871 44
1794389876 44
1794389881 39
1794389886 39
1794389891 41
1794389896 41
1794389901 41
1794389906 41
1794389911 41
1794389916 41
1794389921 43
1794389926 43
```
</details>

---

