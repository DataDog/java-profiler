---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 70-78 cores)</summary>

```
1794945020 70
1794945025 70
1794945030 75
1794945035 75
1794945040 75
1794945045 75
1794945050 75
1794945055 75
1794945060 75
1794945066 75
1794945071 75
1794945076 75
1794945081 75
1794945086 75
1794945091 75
1794945096 78
1794945101 78
1794945106 78
1794945111 78
1794945116 78
```
</details>

---

