---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-26 01:03:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1790398387 36
1790398392 36
1790398397 36
1790398402 36
1790398407 36
1790398412 36
1790398418 36
1790398423 36
1790398428 36
1790398433 36
1790398438 36
1790398443 36
1790398448 36
1790398453 36
1790398458 36
1790398463 36
1790398468 36
1790398473 36
1790398478 36
1790398483 36
```
</details>

---

