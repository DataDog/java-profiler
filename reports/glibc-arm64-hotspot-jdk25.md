---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1795442389 48
1795442394 48
1795442399 48
1795442404 48
1795442409 48
1795442414 48
1795442419 48
1795442424 48
1795442429 48
1795442434 48
1795442439 48
1795442444 48
1795442449 48
1795442454 48
1795442459 43
1795442464 43
1795442469 38
1795442474 38
1795442479 38
1795442484 38
```
</details>

---

