---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1792403380 59
1792403385 59
1792403390 59
1792403395 59
1792403400 59
1792403405 59
1792403410 59
1792403415 59
1792403420 59
1792403425 59
1792403430 59
1792403435 61
1792403440 61
1792403446 59
1792403451 59
1792403456 59
1792403461 59
1792403466 59
1792403471 59
1792403476 59
```
</details>

---

