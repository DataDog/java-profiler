---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-11 11:15:04 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1791731362 12
1791731367 12
1791731372 12
1791731377 12
1791731382 12
1791731387 12
1791731392 12
1791731397 12
1791731402 12
1791731407 17
1791731412 17
1791731417 17
1791731422 17
1791731427 17
1791731432 17
1791731437 17
1791731442 17
1791731447 17
1791731452 17
1791731457 17
```
</details>

---

