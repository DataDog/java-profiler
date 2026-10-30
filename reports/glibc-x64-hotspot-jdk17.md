---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 06:16:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1793355102 60
1793355107 60
1793355112 60
1793355117 60
1793355122 60
1793355127 60
1793355132 60
1793355137 60
1793355142 60
1793355147 60
1793355152 60
1793355157 62
1793355162 62
1793355167 62
1793355172 64
1793355177 64
1793355182 64
1793355187 64
1793355192 64
1793355197 64
```
</details>

---

