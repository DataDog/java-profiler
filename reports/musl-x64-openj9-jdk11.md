---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-11 11:15:04 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 8 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (5 unique values: 24-96 cores)</summary>

```
1791731342 24
1791731347 24
1791731352 41
1791731357 41
1791731362 41
1791731367 41
1791731372 79
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
```
</details>

---

