---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-20 21:19:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1789953266 34
1789953271 34
1789953276 34
1789953281 34
1789953286 34
1789953291 34
1789953296 34
1789953301 34
1789953306 34
1789953311 34
1789953316 34
1789953321 34
1789953326 34
1789953331 34
1789953336 34
1789953341 34
1789953346 34
1789953351 34
1789953356 34
1789953361 29
```
</details>

---

