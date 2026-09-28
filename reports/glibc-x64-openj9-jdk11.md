---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 06:45:41 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 45-56 cores)</summary>

```
1790592069 47
1790592074 47
1790592079 47
1790592084 47
1790592089 47
1790592094 47
1790592099 47
1790592104 47
1790592109 47
1790592114 47
1790592119 47
1790592124 47
1790592129 47
1790592134 47
1790592139 47
1790592144 47
1790592149 45
1790592154 45
1790592159 45
1790592164 45
```
</details>

---

