---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:01:15 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 59-67 cores)</summary>

```
1794326089 65
1794326094 65
1794326099 65
1794326104 67
1794326109 67
1794326114 67
1794326119 67
1794326124 67
1794326129 67
1794326134 67
1794326139 67
1794326144 67
1794326149 67
1794326154 67
1794326159 67
1794326164 59
1794326169 59
1794326174 59
1794326179 59
1794326184 59
```
</details>

---

