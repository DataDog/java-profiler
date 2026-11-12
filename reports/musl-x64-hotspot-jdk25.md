---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:09 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 60-77 cores)</summary>

```
1794487389 60
1794487394 60
1794487399 60
1794487404 60
1794487409 60
1794487414 60
1794487419 60
1794487424 60
1794487429 60
1794487434 60
1794487439 60
1794487444 60
1794487449 60
1794487454 60
1794487459 60
1794487464 60
1794487469 60
1794487474 77
1794487479 77
1794487484 77
```
</details>

---

