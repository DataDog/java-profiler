---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:01:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1794585408 78
1794585413 78
1794585418 78
1794585423 78
1794585428 78
1794585433 78
1794585438 76
1794585443 76
1794585448 76
1794585453 76
1794585458 76
1794585463 76
1794585468 76
1794585473 76
1794585478 76
1794585483 76
1794585488 76
1794585493 76
1794585498 76
1794585503 76
```
</details>

---

