---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 70-85 cores)</summary>

```
1790096719 71
1790096724 71
1790096729 71
1790096734 70
1790096739 70
1790096744 70
1790096749 70
1790096754 70
1790096759 70
1790096764 72
1790096769 72
1790096774 72
1790096779 72
1790096784 72
1790096789 70
1790096794 70
1790096799 70
1790096804 72
1790096809 72
1790096814 75
```
</details>

---

