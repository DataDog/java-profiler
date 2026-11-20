---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 14:01:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 11 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (2 unique values: 59-68 cores)</summary>

```
1795200994 59
1795200999 59
1795201004 59
1795201009 59
1795201014 68
1795201019 68
1795201024 68
1795201029 68
1795201034 68
1795201039 68
1795201044 68
1795201049 68
1795201054 68
1795201059 68
1795201064 68
1795201069 68
1795201074 68
1795201079 68
1795201084 68
1795201089 68
```
</details>

---

