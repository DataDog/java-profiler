---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 07:37:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790336048 50
1790336053 50
1790336058 50
1790336063 50
1790336068 50
1790336073 50
1790336078 50
1790336083 50
1790336088 50
1790336093 50
1790336098 50
1790336103 50
1790336108 50
1790336114 50
1790336119 50
1790336124 50
1790336129 50
1790336134 50
1790336139 50
1790336144 50
```
</details>

---

