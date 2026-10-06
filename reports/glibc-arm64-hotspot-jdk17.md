---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 11:23:36 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 7 |
| Allocations | 98 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (5 unique values: 33-51 cores)</summary>

```
1791299940 38
1791299945 38
1791299950 38
1791299955 33
1791299960 33
1791299965 33
1791299970 33
1791299975 33
1791299980 33
1791299986 41
1791299991 41
1791299996 46
1791300001 46
1791300006 51
1791300011 51
1791300016 51
1791300021 51
1791300026 51
1791300031 51
1791300036 51
```
</details>

---

