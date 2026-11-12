---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 52-70 cores)</summary>

```
1794484073 52
1794484078 52
1794484083 52
1794484088 52
1794484093 52
1794484098 52
1794484103 52
1794484108 52
1794484113 52
1794484118 52
1794484123 52
1794484128 52
1794484133 52
1794484138 52
1794484143 70
1794484148 70
1794484153 68
1794484158 68
1794484163 68
1794484168 68
```
</details>

---

