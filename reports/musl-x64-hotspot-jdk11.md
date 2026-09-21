---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 00:57:38 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1789966338 96
1789966343 96
1789966348 96
1789966353 96
1789966358 96
1789966363 96
1789966368 96
1789966373 96
1789966378 96
1789966383 96
1789966388 96
1789966393 79
1789966398 79
1789966403 79
1789966408 79
1789966413 79
1789966418 79
1789966423 79
1789966428 79
1789966433 79
```
</details>

---

