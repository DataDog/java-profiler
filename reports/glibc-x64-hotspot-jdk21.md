---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-11 11:15:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 19-96 cores)</summary>

```
1791731377 79
1791731382 79
1791731387 79
1791731392 79
1791731397 79
1791731402 96
1791731407 96
1791731412 96
1791731417 96
1791731422 28
1791731427 28
1791731432 28
1791731437 28
1791731442 28
1791731447 28
1791731452 28
1791731457 28
1791731462 28
1791731467 28
1791731472 28
```
</details>

---

