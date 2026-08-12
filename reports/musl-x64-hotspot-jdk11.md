---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:18:24 EDT

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
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1786522369 96
1786522374 96
1786522379 94
1786522384 94
1786522389 94
1786522394 94
1786522399 94
1786522404 89
1786522409 89
1786522414 89
1786522419 89
1786522424 89
1786522429 89
1786522434 89
1786522439 89
1786522444 91
1786522449 91
1786522454 91
1786522459 91
1786522464 91
```
</details>

---

