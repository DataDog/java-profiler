---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 13:40:53 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 69-79 cores)</summary>

```
1787074507 71
1787074512 69
1787074517 69
1787074522 69
1787074527 69
1787074532 69
1787074537 69
1787074542 69
1787074547 69
1787074552 69
1787074557 69
1787074562 69
1787074567 71
1787074572 71
1787074577 71
1787074582 71
1787074587 69
1787074592 69
1787074597 79
1787074602 79
```
</details>

---

