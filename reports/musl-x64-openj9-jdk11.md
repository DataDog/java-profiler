---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:22:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1770826260 91
1770826265 91
1770826270 91
1770826275 91
1770826280 91
1770826285 91
1770826290 91
1770826295 91
1770826301 91
1770826306 91
1770826311 91
1770826316 91
1770826321 91
1770826326 91
1770826331 91
1770826336 91
1770826341 91
1770826346 91
1770826351 91
1770826356 89
```
</details>

---

