---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 18:16:56 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 45-53 cores)</summary>

```
1792534419 53
1792534424 53
1792534429 45
1792534434 45
1792534439 45
1792534444 45
1792534449 45
1792534454 45
1792534459 45
1792534464 45
1792534469 45
1792534474 45
1792534479 45
1792534484 45
1792534489 45
1792534494 45
1792534499 45
1792534504 45
1792534509 45
1792534514 45
```
</details>

---

