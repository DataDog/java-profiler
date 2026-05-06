---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 08:41:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 32-37 cores)</summary>

```
1778071084 34
1778071089 34
1778071094 34
1778071099 34
1778071104 34
1778071109 34
1778071114 34
1778071119 34
1778071124 34
1778071129 34
1778071134 34
1778071139 34
1778071144 34
1778071149 34
1778071154 37
1778071159 37
1778071164 37
1778071169 37
1778071174 37
1778071179 37
```
</details>

---

