---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:21:10 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795195058 50
1795195063 50
1795195068 50
1795195073 50
1795195078 50
1795195083 50
1795195088 50
1795195093 50
1795195098 50
1795195103 50
1795195108 50
1795195113 50
1795195118 50
1795195123 50
1795195128 50
1795195133 50
1795195138 50
1795195143 50
1795195148 50
1795195153 50
```
</details>

---

