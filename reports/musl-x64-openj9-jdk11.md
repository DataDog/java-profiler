---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 03:42:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 8 |
| Allocations | 588 |

<details>
<summary>CPU Timeline (2 unique values: 81-86 cores)</summary>

```
1794559111 81
1794559116 81
1794559121 81
1794559126 81
1794559131 81
1794559136 81
1794559141 81
1794559146 81
1794559151 81
1794559156 81
1794559161 81
1794559166 81
1794559171 81
1794559176 81
1794559181 81
1794559186 81
1794559191 81
1794559196 86
1794559201 86
1794559206 86
```
</details>

---

