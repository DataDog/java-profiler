---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 00:57:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 32-36 cores)</summary>

```
1788065569 34
1788065574 34
1788065579 34
1788065584 34
1788065589 34
1788065594 36
1788065599 36
1788065604 36
1788065609 36
1788065614 36
1788065619 36
1788065624 36
1788065629 36
1788065634 36
1788065639 36
1788065644 32
1788065649 32
1788065654 32
1788065659 32
1788065664 32
```
</details>

---

