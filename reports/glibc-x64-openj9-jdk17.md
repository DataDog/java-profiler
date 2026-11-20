---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:21:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 58-62 cores)</summary>

```
1795195009 59
1795195014 59
1795195019 59
1795195024 59
1795195029 59
1795195034 59
1795195039 59
1795195044 59
1795195049 59
1795195054 59
1795195059 62
1795195064 62
1795195069 62
1795195074 62
1795195079 62
1795195084 58
1795195089 58
1795195094 58
1795195099 58
1795195104 58
```
</details>

---

