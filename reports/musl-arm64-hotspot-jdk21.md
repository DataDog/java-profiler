---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:18:51 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 9 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795605033 47
1795605038 47
1795605043 47
1795605048 47
1795605053 47
1795605058 47
1795605063 64
1795605068 64
1795605073 47
1795605078 47
1795605083 47
1795605088 47
1795605093 47
1795605098 47
1795605103 47
1795605108 47
1795605113 47
1795605118 47
1795605123 47
1795605128 47
```
</details>

---

