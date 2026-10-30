---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 13:48:56 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 51 |
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
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 27-51 cores)</summary>

```
1793382261 27
1793382266 27
1793382271 27
1793382276 27
1793382281 27
1793382286 27
1793382291 27
1793382296 27
1793382301 27
1793382306 32
1793382311 32
1793382316 34
1793382321 34
1793382326 51
1793382331 51
1793382336 51
1793382341 51
1793382346 51
1793382351 34
1793382356 34
```
</details>

---

