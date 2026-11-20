---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:21:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 60-67 cores)</summary>

```
1795195004 67
1795195009 67
1795195014 67
1795195019 67
1795195024 67
1795195029 67
1795195034 67
1795195039 67
1795195044 62
1795195049 62
1795195054 62
1795195059 62
1795195064 62
1795195069 62
1795195074 62
1795195079 62
1795195084 62
1795195089 60
1795195094 60
1795195099 60
```
</details>

---

