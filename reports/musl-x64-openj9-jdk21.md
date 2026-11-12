---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:01:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 89-92 cores)</summary>

```
1794480907 91
1794480912 91
1794480917 91
1794480922 91
1794480927 89
1794480932 89
1794480937 92
1794480942 92
1794480947 92
1794480952 92
1794480957 92
1794480962 92
1794480967 92
1794480972 90
1794480977 90
1794480982 90
1794480987 90
1794480992 90
1794480997 90
1794481002 90
```
</details>

---

