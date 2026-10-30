---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 07:23:30 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1793359127 32
1793359132 32
1793359137 32
1793359142 32
1793359147 32
1793359152 32
1793359157 32
1793359162 32
1793359167 32
1793359172 20
1793359177 20
1793359182 20
1793359187 20
1793359192 20
1793359197 20
1793359202 20
1793359207 20
1793359212 20
1793359217 20
1793359222 20
```
</details>

---

