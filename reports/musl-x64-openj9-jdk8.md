---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-23 11:05:05 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 76-80 cores)</summary>

```
1795449478 78
1795449483 78
1795449488 78
1795449493 76
1795449498 76
1795449503 76
1795449508 76
1795449513 76
1795449518 76
1795449523 76
1795449528 76
1795449533 78
1795449538 78
1795449543 78
1795449548 80
1795449553 80
1795449558 80
1795449563 80
1795449568 78
1795449573 78
```
</details>

---

