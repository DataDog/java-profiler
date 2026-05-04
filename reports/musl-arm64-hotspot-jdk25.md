---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:21:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857347 64
1777857352 64
1777857357 64
1777857362 64
1777857367 64
1777857372 64
1777857377 64
1777857382 64
1777857387 64
1777857392 64
1777857397 64
1777857402 64
1777857407 64
1777857412 64
1777857417 64
1777857422 64
1777857427 64
1777857432 64
1777857437 64
1777857442 64
```
</details>

---

