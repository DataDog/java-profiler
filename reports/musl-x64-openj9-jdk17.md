---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:01:56 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 54-61 cores)</summary>

```
1794480906 56
1794480911 56
1794480916 56
1794480921 56
1794480926 56
1794480931 56
1794480936 56
1794480941 54
1794480946 54
1794480951 54
1794480956 54
1794480961 54
1794480966 54
1794480971 54
1794480976 54
1794480981 54
1794480986 54
1794480991 61
1794480996 61
1794481001 61
```
</details>

---

