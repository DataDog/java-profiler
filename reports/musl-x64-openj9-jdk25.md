---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 13:40:56 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 76-80 cores)</summary>

```
1787074517 76
1787074522 76
1787074527 76
1787074532 76
1787074537 76
1787074542 76
1787074547 76
1787074553 76
1787074558 76
1787074563 76
1787074568 76
1787074573 76
1787074578 76
1787074583 76
1787074588 76
1787074593 76
1787074598 80
1787074603 80
1787074608 80
1787074613 80
```
</details>

---

