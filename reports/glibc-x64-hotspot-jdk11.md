---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:46:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 38-66 cores)</summary>

```
1795632034 64
1795632039 64
1795632044 64
1795632049 64
1795632054 64
1795632059 64
1795632064 64
1795632069 64
1795632074 64
1795632079 64
1795632084 64
1795632089 64
1795632094 64
1795632099 64
1795632104 64
1795632109 64
1795632114 64
1795632119 66
1795632124 66
1795632129 66
```
</details>

---

