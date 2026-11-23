---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 52-56 cores)</summary>

```
1795449468 56
1795449473 56
1795449478 56
1795449483 56
1795449488 52
1795449493 52
1795449498 52
1795449503 52
1795449508 52
1795449513 52
1795449518 52
1795449523 52
1795449528 52
1795449533 52
1795449538 52
1795449543 52
1795449548 52
1795449553 52
1795449558 52
1795449563 52
```
</details>

---

