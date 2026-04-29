---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:09:01 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1777475047 94
1777475052 94
1777475057 96
1777475062 96
1777475067 96
1777475072 96
1777475077 96
1777475082 96
1777475087 96
1777475092 96
1777475097 96
1777475102 96
1777475107 96
1777475112 96
1777475117 96
1777475122 96
1777475128 91
1777475133 91
1777475138 91
1777475143 91
```
</details>

---

