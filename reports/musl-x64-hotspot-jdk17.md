---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:21:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (5 unique values: 37-67 cores)</summary>

```
1795195014 40
1795195019 40
1795195024 40
1795195029 40
1795195034 40
1795195039 40
1795195044 67
1795195049 67
1795195054 67
1795195059 39
1795195064 39
1795195069 37
1795195074 37
1795195079 37
1795195084 37
1795195089 37
1795195094 37
1795195099 37
1795195104 37
1795195109 37
```
</details>

---

