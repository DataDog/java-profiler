---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 12:19:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795540543 59
1795540548 59
1795540553 54
1795540558 54
1795540563 54
1795540568 54
1795540573 54
1795540578 54
1795540583 54
1795540588 54
1795540593 54
1795540598 54
1795540603 54
1795540608 54
1795540613 54
1795540618 54
1795540623 54
1795540628 54
1795540633 59
1795540638 59
```
</details>

---

