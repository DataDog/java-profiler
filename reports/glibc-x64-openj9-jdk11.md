---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 10:47:06 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1773240063 30
1773240068 30
1773240073 28
1773240078 28
1773240083 28
1773240089 28
1773240094 30
1773240099 30
1773240104 30
1773240109 30
1773240114 30
1773240119 30
1773240124 30
1773240129 32
1773240134 32
1773240139 32
1773240144 32
1773240149 32
1773240154 32
1773240159 32
```
</details>

---

