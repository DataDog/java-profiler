---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:01:56 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1794480908 94
1794480913 94
1794480918 96
1794480923 96
1794480928 96
1794480934 96
1794480939 96
1794480944 96
1794480949 96
1794480954 96
1794480959 96
1794480964 96
1794480969 96
1794480974 96
1794480979 96
1794480984 96
1794480989 96
1794480994 96
1794480999 96
1794481004 96
```
</details>

---

