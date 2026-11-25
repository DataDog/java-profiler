---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:18:52 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 83-94 cores)</summary>

```
1795605013 83
1795605018 83
1795605023 85
1795605028 85
1795605033 85
1795605038 85
1795605043 83
1795605048 83
1795605053 83
1795605058 83
1795605063 83
1795605068 83
1795605073 92
1795605078 92
1795605083 92
1795605088 94
1795605093 94
1795605098 94
1795605103 94
1795605108 94
```
</details>

---

