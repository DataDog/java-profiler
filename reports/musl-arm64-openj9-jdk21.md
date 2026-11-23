---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 15.37/sec |
| Health Score | 961% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 39-49 cores)</summary>

```
1795449513 39
1795449518 39
1795449523 44
1795449528 44
1795449533 44
1795449538 44
1795449543 49
1795449548 49
1795449553 49
1795449558 49
1795449563 49
1795449568 49
1795449573 49
1795449578 49
1795449583 49
1795449588 49
1795449593 49
1795449599 49
1795449604 49
1795449609 49
```
</details>

---

