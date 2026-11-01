---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-01 01:04:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 60-66 cores)</summary>

```
1793509231 66
1793509236 66
1793509241 64
1793509246 64
1793509251 62
1793509256 62
1793509261 60
1793509266 60
1793509271 60
1793509276 60
1793509281 62
1793509286 62
1793509291 64
1793509296 64
1793509301 64
1793509306 64
1793509311 64
1793509316 64
1793509321 64
1793509326 64
```
</details>

---

