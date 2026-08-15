---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-15 05:47:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786787028 46
1786787033 46
1786787038 48
1786787043 48
1786787048 48
1786787053 48
1786787058 48
1786787063 48
1786787068 48
1786787073 48
1786787078 48
1786787083 48
1786787088 48
1786787093 48
1786787098 48
1786787103 48
1786787108 48
1786787113 48
1786787118 48
1786787123 48
```
</details>

---

