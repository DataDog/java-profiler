---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 09:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792156028 48
1792156033 48
1792156038 48
1792156043 48
1792156048 48
1792156053 48
1792156058 48
1792156063 48
1792156068 48
1792156073 48
1792156078 48
1792156083 48
1792156088 48
1792156093 43
1792156098 43
1792156103 43
1792156108 43
1792156113 43
1792156118 43
1792156123 43
```
</details>

---

