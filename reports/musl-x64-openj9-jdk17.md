---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:21:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 314 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 50-84 cores)</summary>

```
1795195014 84
1795195019 84
1795195024 69
1795195029 69
1795195034 69
1795195039 69
1795195044 52
1795195049 52
1795195054 52
1795195059 52
1795195064 52
1795195069 52
1795195074 52
1795195079 52
1795195084 52
1795195089 50
1795195094 50
1795195099 50
1795195104 50
1795195109 50
```
</details>

---

