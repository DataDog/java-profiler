---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 21:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 43-73 cores)</summary>

```
1790558246 51
1790558251 51
1790558256 51
1790558261 51
1790558266 51
1790558271 51
1790558276 43
1790558281 43
1790558286 43
1790558291 43
1790558296 43
1790558301 43
1790558306 43
1790558311 43
1790558316 43
1790558321 43
1790558326 43
1790558331 43
1790558336 43
1790558341 43
```
</details>

---

