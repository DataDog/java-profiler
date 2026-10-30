---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 12:40:39 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793378195 51
1793378201 51
1793378206 51
1793378211 51
1793378216 51
1793378221 51
1793378226 51
1793378231 51
1793378236 51
1793378241 51
1793378246 51
1793378251 51
1793378256 51
1793378261 51
1793378266 51
1793378271 51
1793378276 46
1793378281 46
1793378286 46
1793378291 46
```
</details>

---

