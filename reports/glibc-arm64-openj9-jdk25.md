---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 05:55:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 8 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 12-14 cores)</summary>

```
1793703074 12
1793703079 12
1793703084 12
1793703089 12
1793703094 12
1793703099 12
1793703104 12
1793703109 12
1793703114 12
1793703119 12
1793703124 12
1793703129 12
1793703134 12
1793703139 12
1793703144 12
1793703149 12
1793703154 12
1793703159 12
1793703164 14
1793703169 14
```
</details>

---

