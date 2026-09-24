---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790238326 43
1790238331 43
1790238336 43
1790238341 38
1790238346 38
1790238351 38
1790238356 38
1790238361 43
1790238366 43
1790238371 43
1790238376 43
1790238381 43
1790238386 43
1790238391 43
1790238396 43
1790238401 43
1790238406 48
1790238411 48
1790238416 48
1790238421 48
```
</details>

---

