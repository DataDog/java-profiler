---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 71-78 cores)</summary>

```
1794484114 71
1794484119 71
1794484124 71
1794484129 71
1794484134 71
1794484139 73
1794484144 73
1794484149 73
1794484154 73
1794484159 73
1794484164 73
1794484169 73
1794484174 78
1794484179 78
1794484184 78
1794484189 74
1794484194 74
1794484199 74
1794484204 74
1794484209 72
```
</details>

---

