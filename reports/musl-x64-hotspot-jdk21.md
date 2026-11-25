---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:45:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 65-93 cores)</summary>

```
1795642890 65
1795642895 65
1795642900 65
1795642905 65
1795642911 65
1795642916 65
1795642921 65
1795642926 65
1795642931 65
1795642936 67
1795642941 67
1795642946 67
1795642951 67
1795642956 67
1795642961 67
1795642966 67
1795642971 67
1795642976 67
1795642981 67
1795642986 67
```
</details>

---

