---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-01 09:14:15 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 49-54 cores)</summary>

```
1777640926 54
1777640931 54
1777640936 54
1777640941 54
1777640946 54
1777640951 54
1777640956 54
1777640961 54
1777640966 54
1777640971 54
1777640976 54
1777640981 54
1777640986 54
1777640991 54
1777640996 49
1777641001 49
1777641006 49
1777641011 49
1777641016 49
1777641021 49
```
</details>

---

