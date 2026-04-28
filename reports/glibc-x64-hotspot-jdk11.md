---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:45:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
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
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (2 unique values: 36-40 cores)</summary>

```
1777394358 36
1777394363 40
1777394368 40
1777394373 40
1777394378 40
1777394383 40
1777394388 40
1777394393 40
1777394398 40
1777394403 40
1777394408 40
1777394413 40
1777394418 40
1777394423 40
1777394428 40
1777394433 40
1777394438 40
1777394443 40
1777394448 40
1777394453 40
```
</details>

---

