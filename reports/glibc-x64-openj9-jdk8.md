---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1794484068 72
1794484073 72
1794484079 72
1794484084 72
1794484089 72
1794484094 72
1794484099 72
1794484104 70
1794484109 70
1794484114 70
1794484119 70
1794484124 70
1794484129 70
1794484134 72
1794484139 72
1794484144 72
1794484149 72
1794484154 72
1794484159 72
1794484164 72
```
</details>

---

