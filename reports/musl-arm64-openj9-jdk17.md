---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 10:05:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1778507972 44
1778507977 44
1778507982 44
1778507987 44
1778507992 44
1778507997 44
1778508002 44
1778508007 44
1778508012 44
1778508017 44
1778508022 44
1778508027 44
1778508032 44
1778508037 44
1778508042 44
1778508047 44
1778508052 44
1778508057 39
1778508062 39
1778508067 39
```
</details>

---

