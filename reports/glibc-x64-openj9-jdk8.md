---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-24 05:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 52-75 cores)</summary>

```
1790241533 73
1790241538 73
1790241543 73
1790241548 73
1790241553 73
1790241558 73
1790241563 73
1790241568 73
1790241573 73
1790241578 75
1790241583 75
1790241588 75
1790241593 75
1790241598 75
1790241603 75
1790241608 75
1790241613 75
1790241618 52
1790241623 52
1790241628 52
```
</details>

---

