---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1795449473 91
1795449478 91
1795449483 91
1795449488 91
1795449493 91
1795449498 91
1795449503 91
1795449508 91
1795449513 91
1795449518 91
1795449523 91
1795449528 91
1795449533 91
1795449538 89
1795449543 89
1795449548 89
1795449553 89
1795449558 89
1795449563 87
1795449568 87
```
</details>

---

