---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 23-27 cores)</summary>

```
1770137424 27
1770137429 27
1770137434 27
1770137439 27
1770137444 27
1770137449 27
1770137454 27
1770137459 23
1770137464 23
1770137469 23
1770137474 23
1770137479 23
1770137484 23
1770137489 23
1770137494 23
1770137499 23
1770137504 23
1770137509 23
1770137514 23
1770137519 23
```
</details>

---

