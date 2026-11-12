---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:33:52 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (7 unique values: 61-77 cores)</summary>

```
1794508078 61
1794508083 61
1794508088 61
1794508093 61
1794508098 67
1794508103 67
1794508109 67
1794508114 69
1794508119 69
1794508124 69
1794508129 69
1794508134 69
1794508139 74
1794508144 74
1794508149 72
1794508154 72
1794508159 72
1794508164 72
1794508169 72
1794508174 74
```
</details>

---

