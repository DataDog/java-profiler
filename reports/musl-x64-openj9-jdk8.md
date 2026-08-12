---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-12 04:18:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 71-81 cores)</summary>

```
1786522367 73
1786522372 73
1786522377 73
1786522382 73
1786522387 73
1786522392 73
1786522397 73
1786522402 73
1786522407 73
1786522412 73
1786522417 71
1786522422 71
1786522427 71
1786522432 71
1786522437 71
1786522442 71
1786522447 71
1786522452 74
1786522457 74
1786522462 76
```
</details>

---

