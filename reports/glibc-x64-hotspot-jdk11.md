---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:19:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 75-92 cores)</summary>

```
1794582922 75
1794582927 75
1794582932 75
1794582937 75
1794582942 75
1794582947 75
1794582952 75
1794582957 75
1794582962 75
1794582967 75
1794582972 75
1794582977 75
1794582982 75
1794582987 92
1794582992 92
1794582997 92
1794583002 92
1794583007 92
1794583012 92
1794583017 92
```
</details>

---

