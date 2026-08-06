---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-06 07:13:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 10 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1786014523 27
1786014528 27
1786014533 27
1786014538 27
1786014543 27
1786014548 30
1786014553 30
1786014558 30
1786014563 30
1786014568 30
1786014573 30
1786014578 30
1786014583 30
1786014588 30
1786014593 30
1786014598 30
1786014603 30
1786014608 30
1786014613 30
1786014618 30
```
</details>

---

