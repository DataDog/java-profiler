---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 10:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1787151250 96
1787151255 79
1787151260 79
1787151265 79
1787151270 79
1787151275 79
1787151280 79
1787151285 79
1787151290 79
1787151295 94
1787151300 94
1787151306 94
1787151311 94
1787151316 94
1787151321 94
1787151326 94
1787151331 94
1787151336 94
1787151341 94
1787151346 94
```
</details>

---

