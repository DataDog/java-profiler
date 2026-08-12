---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:18:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 39-52 cores)</summary>

```
1786522382 39
1786522387 39
1786522392 39
1786522397 39
1786522402 39
1786522407 39
1786522412 52
1786522417 52
1786522422 52
1786522427 52
1786522432 52
1786522437 52
1786522442 52
1786522447 52
1786522452 52
1786522457 52
1786522462 52
1786522467 52
1786522472 52
1786522477 52
```
</details>

---

