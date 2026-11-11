---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:06:29 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (1 unique values: 25-25 cores)</summary>

```
1794430865 25
1794430870 25
1794430875 25
1794430880 25
1794430885 25
1794430890 25
1794430895 25
1794430900 25
1794430905 25
1794430910 25
1794430916 25
1794430921 25
1794430926 25
1794430931 25
1794430936 25
1794430941 25
1794430946 25
1794430951 25
1794430956 25
1794430961 25
```
</details>

---

