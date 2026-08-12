---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1786547915 58
1786547920 58
1786547925 58
1786547930 58
1786547935 58
1786547940 60
1786547945 60
1786547950 60
1786547955 60
1786547960 62
1786547965 62
1786547970 62
1786547975 62
1786547980 62
1786547985 62
1786547990 62
1786547995 62
1786548000 62
1786548005 62
1786548010 62
```
</details>

---

