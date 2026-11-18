---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:35:55 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 27-59 cores)</summary>

```
1794997802 59
1794997807 59
1794997812 59
1794997817 30
1794997822 30
1794997827 30
1794997832 30
1794997837 30
1794997842 30
1794997847 30
1794997852 30
1794997857 27
1794997862 27
1794997867 27
1794997872 27
1794997877 27
1794997882 27
1794997887 27
1794997892 27
1794997897 27
```
</details>

---

