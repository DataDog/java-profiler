---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:19:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 14 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794582907 51
1794582912 51
1794582917 51
1794582922 51
1794582927 51
1794582932 51
1794582937 51
1794582942 51
1794582947 51
1794582952 51
1794582957 51
1794582962 51
1794582967 51
1794582972 51
1794582977 51
1794582982 64
1794582987 64
1794582992 64
1794582997 64
1794583002 64
```
</details>

---

