---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:47:19 EST

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 9 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 11 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794310988 48
1794310993 48
1794310998 48
1794311003 48
1794311009 48
1794311014 48
1794311019 48
1794311024 44
1794311029 44
1794311034 44
1794311039 44
1794311044 44
1794311049 44
1794311054 44
1794311059 44
1794311064 44
1794311069 44
1794311074 44
1794311079 44
1794311084 44
```
</details>

---

