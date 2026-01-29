---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 11:12:23 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 17.13/sec |
| Health Score | 1071% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 24.40/sec |
| Health Score | 1525% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (6 unique values: 79-87 cores)</summary>

```
1769702966 79
1769702971 79
1769702976 79
1769702981 79
1769702986 79
1769702991 79
1769702996 79
1769703001 82
1769703006 82
1769703011 82
1769703016 82
1769703021 82
1769703026 84
1769703031 84
1769703036 84
1769703041 84
1769703046 84
1769703051 84
1769703056 81
1769703061 81
```
</details>

---

