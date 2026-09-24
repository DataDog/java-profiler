---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:24:28 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 12 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1790241528 40
1790241533 40
1790241538 40
1790241543 40
1790241548 40
1790241553 40
1790241558 40
1790241563 40
1790241568 45
1790241573 45
1790241578 45
1790241583 45
1790241588 45
1790241593 45
1790241598 45
1790241603 45
1790241608 46
1790241613 46
1790241618 43
1790241623 43
```
</details>

---

