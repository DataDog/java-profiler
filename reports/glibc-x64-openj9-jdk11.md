---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:34:09 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 65-85 cores)</summary>

```
1793125657 85
1793125662 85
1793125667 85
1793125672 85
1793125677 85
1793125682 65
1793125687 65
1793125692 67
1793125697 67
1793125702 67
1793125707 67
1793125712 67
1793125717 67
1793125722 67
1793125727 67
1793125732 67
1793125737 67
1793125742 67
1793125747 67
1793125752 67
```
</details>

---

