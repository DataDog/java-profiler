---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 20:17:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 48-56 cores)</summary>

```
1786407097 48
1786407102 48
1786407107 48
1786407112 48
1786407117 48
1786407122 48
1786407127 48
1786407132 48
1786407137 48
1786407142 48
1786407147 48
1786407152 48
1786407157 48
1786407162 48
1786407167 48
1786407172 52
1786407177 52
1786407182 52
1786407187 52
1786407192 56
```
</details>

---

