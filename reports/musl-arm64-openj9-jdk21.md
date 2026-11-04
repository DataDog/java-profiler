---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:47:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 12 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793788910 48
1793788915 48
1793788920 48
1793788925 48
1793788930 48
1793788935 43
1793788940 43
1793788945 43
1793788950 43
1793788955 43
1793788960 43
1793788965 43
1793788970 43
1793788975 43
1793788980 43
1793788985 43
1793788990 43
1793788995 48
1793789000 48
1793789005 48
```
</details>

---

