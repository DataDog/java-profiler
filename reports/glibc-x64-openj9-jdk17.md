---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 15:09:09 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1786474984 87
1786474989 87
1786474994 87
1786474999 89
1786475004 89
1786475009 89
1786475014 87
1786475019 87
1786475024 87
1786475029 87
1786475034 87
1786475039 85
1786475044 85
1786475049 85
1786475054 85
1786475059 85
1786475064 85
1786475069 85
1786475074 87
1786475079 87
```
</details>

---

