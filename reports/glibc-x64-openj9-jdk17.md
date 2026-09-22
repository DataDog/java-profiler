---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:28:35 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (5 unique values: 53-94 cores)</summary>

```
1790094067 55
1790094072 55
1790094077 55
1790094082 55
1790094087 53
1790094092 53
1790094097 53
1790094102 53
1790094107 53
1790094112 53
1790094117 53
1790094122 53
1790094127 94
1790094132 94
1790094137 56
1790094142 56
1790094147 56
1790094152 56
1790094157 58
1790094162 58
```
</details>

---

