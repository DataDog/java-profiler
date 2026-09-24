---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1002 |
| Sample Rate | 16.70/sec |
| Health Score | 1044% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790241523 48
1790241528 48
1790241533 48
1790241538 48
1790241543 48
1790241548 48
1790241553 48
1790241558 48
1790241563 48
1790241568 48
1790241573 48
1790241578 48
1790241583 48
1790241588 48
1790241593 48
1790241598 48
1790241603 48
1790241608 48
1790241613 48
1790241618 48
```
</details>

---

