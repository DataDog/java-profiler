---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 10:08:05 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (6 unique values: 81-96 cores)</summary>

```
1792505001 89
1792505006 89
1792505011 89
1792505016 89
1792505021 89
1792505026 84
1792505031 84
1792505036 86
1792505041 86
1792505046 86
1792505051 86
1792505056 86
1792505061 86
1792505066 81
1792505071 81
1792505076 81
1792505081 91
1792505086 91
1792505091 91
1792505096 91
```
</details>

---

