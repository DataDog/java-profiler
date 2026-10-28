---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 11:29:55 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1793201097 27
1793201102 27
1793201107 27
1793201112 27
1793201117 27
1793201122 27
1793201127 27
1793201132 27
1793201137 27
1793201142 27
1793201147 27
1793201152 27
1793201157 27
1793201162 27
1793201167 27
1793201172 30
1793201177 30
1793201182 30
1793201187 30
1793201192 30
```
</details>

---

