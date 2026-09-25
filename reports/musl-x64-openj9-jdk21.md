---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 07:37:34 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1790336065 62
1790336070 54
1790336075 54
1790336080 54
1790336085 54
1790336090 54
1790336095 54
1790336100 54
1790336105 54
1790336110 54
1790336115 54
1790336120 52
1790336125 52
1790336131 52
1790336136 52
1790336141 52
1790336146 52
1790336151 52
1790336156 52
1790336161 52
```
</details>

---

