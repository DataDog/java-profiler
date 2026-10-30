---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:16:23 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793355122 30
1793355127 30
1793355132 30
1793355137 30
1793355142 30
1793355147 30
1793355152 30
1793355157 28
1793355162 28
1793355167 28
1793355172 28
1793355177 28
1793355182 28
1793355187 28
1793355192 28
1793355197 30
1793355202 30
1793355207 30
1793355212 30
1793355217 30
```
</details>

---

