---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 05:55:14 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1793703016 10
1793703021 10
1793703026 10
1793703031 10
1793703036 10
1793703041 10
1793703046 10
1793703051 10
1793703056 10
1793703061 10
1793703066 15
1793703071 15
1793703076 15
1793703081 15
1793703086 15
1793703091 15
1793703096 15
1793703101 15
1793703106 15
1793703111 15
```
</details>

---

