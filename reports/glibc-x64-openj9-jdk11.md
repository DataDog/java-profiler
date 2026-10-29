---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 58-66 cores)</summary>

```
1793288571 58
1793288576 58
1793288581 58
1793288586 58
1793288591 58
1793288596 58
1793288601 58
1793288606 59
1793288611 59
1793288616 59
1793288621 62
1793288626 62
1793288631 62
1793288636 62
1793288641 62
1793288646 62
1793288651 62
1793288656 62
1793288661 66
1793288666 66
```
</details>

---

