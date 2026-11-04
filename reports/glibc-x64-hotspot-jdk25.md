---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 18:30:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 19-59 cores)</summary>

```
1793834777 54
1793834782 54
1793834787 57
1793834792 57
1793834797 57
1793834802 57
1793834807 57
1793834812 57
1793834817 57
1793834822 57
1793834827 57
1793834832 57
1793834837 59
1793834842 59
1793834847 59
1793834852 59
1793834857 59
1793834862 59
1793834867 59
1793834872 59
```
</details>

---

