---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 12:19:04 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 76-84 cores)</summary>

```
1794590077 76
1794590082 76
1794590087 76
1794590092 76
1794590097 76
1794590102 77
1794590107 77
1794590112 77
1794590117 77
1794590122 82
1794590127 82
1794590132 80
1794590137 80
1794590142 80
1794590147 80
1794590152 80
1794590157 80
1794590162 80
1794590167 82
1794590172 82
```
</details>

---

