---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:44:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789731626 94
1789731631 94
1789731636 94
1789731641 94
1789731646 96
1789731651 96
1789731656 94
1789731661 94
1789731666 94
1789731671 94
1789731676 94
1789731681 94
1789731686 94
1789731691 94
1789731696 94
1789731701 96
1789731706 96
1789731711 96
1789731716 96
1789731721 96
```
</details>

---

