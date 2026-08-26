---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 14:48:33 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 11 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (3 unique values: 35-44 cores)</summary>

```
1787769817 44
1787769822 44
1787769827 44
1787769832 44
1787769837 40
1787769842 40
1787769847 40
1787769852 40
1787769857 40
1787769862 40
1787769867 40
1787769872 40
1787769877 40
1787769882 40
1787769887 40
1787769892 40
1787769897 40
1787769902 40
1787769907 35
1787769912 35
```
</details>

---

