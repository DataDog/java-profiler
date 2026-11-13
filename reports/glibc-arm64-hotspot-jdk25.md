---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:22:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 11 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794582927 48
1794582932 48
1794582937 48
1794582942 48
1794582947 48
1794582952 48
1794582957 48
1794582962 48
1794582967 48
1794582972 48
1794582977 48
1794582982 48
1794582987 48
1794582992 48
1794582997 48
1794583002 43
1794583007 43
1794583012 43
1794583017 43
1794583022 43
```
</details>

---

