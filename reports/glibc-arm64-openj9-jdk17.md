---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 08:18:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1791375246 43
1791375251 43
1791375256 43
1791375261 43
1791375266 43
1791375271 43
1791375276 43
1791375281 43
1791375286 43
1791375291 43
1791375296 43
1791375301 47
1791375306 47
1791375311 51
1791375316 51
1791375321 51
1791375326 51
1791375331 51
1791375336 51
1791375341 51
```
</details>

---

