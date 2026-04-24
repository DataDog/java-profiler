---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-24 12:55:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1777049464 29
1777049469 29
1777049474 29
1777049479 29
1777049484 29
1777049489 29
1777049494 27
1777049499 27
1777049504 27
1777049509 29
1777049514 29
1777049519 29
1777049524 29
1777049529 27
1777049534 27
1777049539 29
1777049544 29
1777049549 30
1777049554 30
1777049559 30
```
</details>

---

