---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-12 05:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1791798659 94
1791798664 86
1791798669 86
1791798674 86
1791798679 86
1791798684 86
1791798689 86
1791798694 86
1791798699 86
1791798704 86
1791798709 86
1791798714 86
1791798719 86
1791798724 88
1791798729 88
1791798734 88
1791798739 88
1791798744 88
1791798749 88
1791798754 88
```
</details>

---

