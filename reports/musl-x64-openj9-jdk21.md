---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:55:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1794484063 90
1794484068 90
1794484073 90
1794484078 90
1794484083 90
1794484088 90
1794484093 90
1794484098 90
1794484103 88
1794484108 88
1794484113 88
1794484118 88
1794484123 86
1794484128 86
1794484133 86
1794484138 86
1794484143 86
1794484148 86
1794484153 86
1794484158 88
```
</details>

---

