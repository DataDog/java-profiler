---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:55:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (4 unique values: 63-87 cores)</summary>

```
1794484083 87
1794484088 87
1794484093 87
1794484098 87
1794484103 87
1794484108 87
1794484113 87
1794484118 87
1794484123 87
1794484128 87
1794484133 87
1794484138 87
1794484143 87
1794484148 87
1794484153 87
1794484158 87
1794484163 87
1794484168 87
1794484173 83
1794484178 83
```
</details>

---

