---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 10:58:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787151341 96
1787151347 96
1787151352 96
1787151357 96
1787151362 96
1787151367 96
1787151372 96
1787151377 94
1787151382 94
1787151387 94
1787151392 94
1787151397 94
1787151402 94
1787151407 94
1787151412 94
1787151417 94
1787151422 94
1787151427 94
1787151432 94
1787151437 94
```
</details>

---

