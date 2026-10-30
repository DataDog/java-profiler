---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 12:40:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 12 |
| Allocations | 216 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793378176 48
1793378181 48
1793378186 48
1793378191 48
1793378196 48
1793378201 48
1793378206 48
1793378211 48
1793378216 48
1793378221 48
1793378226 48
1793378231 48
1793378236 48
1793378241 36
1793378246 36
1793378251 36
1793378256 36
1793378261 36
1793378266 36
1793378271 36
```
</details>

---

