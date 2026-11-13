---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 12:24:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794590358 32
1794590363 32
1794590368 32
1794590373 32
1794590378 32
1794590383 32
1794590388 32
1794590393 32
1794590398 32
1794590403 32
1794590408 32
1794590413 32
1794590418 32
1794590423 32
1794590428 32
1794590433 32
1794590439 32
1794590444 32
1794590449 32
1794590454 30
```
</details>

---

