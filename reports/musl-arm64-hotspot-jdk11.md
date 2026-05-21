---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-21 08:14:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 11 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1779365399 64
1779365404 64
1779365409 64
1779365414 64
1779365419 64
1779365424 64
1779365429 64
1779365434 64
1779365439 64
1779365444 64
1779365449 64
1779365454 64
1779365459 64
1779365464 64
1779365469 64
1779365474 64
1779365479 64
1779365484 64
1779365490 64
1779365495 64
```
</details>

---

