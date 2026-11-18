---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:38:22 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1795001594 70
1795001599 70
1795001604 70
1795001609 70
1795001614 70
1795001619 74
1795001624 74
1795001629 74
1795001634 74
1795001639 74
1795001644 74
1795001650 74
1795001655 74
1795001660 74
1795001665 74
1795001670 74
1795001675 74
1795001680 74
1795001685 74
1795001690 74
```
</details>

---

