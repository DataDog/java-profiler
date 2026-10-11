---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-11 11:15:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791731357 30
1791731362 30
1791731367 30
1791731372 30
1791731377 30
1791731382 30
1791731387 30
1791731392 30
1791731397 30
1791731402 30
1791731407 30
1791731412 30
1791731417 30
1791731422 30
1791731427 30
1791731432 30
1791731437 30
1791731442 30
1791731447 30
1791731452 32
```
</details>

---

