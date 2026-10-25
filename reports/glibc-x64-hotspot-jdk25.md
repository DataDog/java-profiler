---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-25 06:56:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 349 |
| Sample Rate | 5.82/sec |
| Health Score | 364% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 65-96 cores)</summary>

```
1792925357 96
1792925362 96
1792925367 96
1792925372 96
1792925377 96
1792925382 96
1792925387 96
1792925392 96
1792925397 96
1792925402 96
1792925407 96
1792925412 96
1792925417 96
1792925422 96
1792925427 96
1792925432 96
1792925437 96
1792925442 96
1792925447 96
1792925452 65
```
</details>

---

