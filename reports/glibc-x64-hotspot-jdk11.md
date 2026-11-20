---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:42:05 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1795174626 76
1795174631 76
1795174636 76
1795174641 76
1795174646 76
1795174651 74
1795174656 74
1795174661 74
1795174666 74
1795174671 74
1795174676 74
1795174681 74
1795174686 74
1795174691 74
1795174696 74
1795174701 74
1795174706 74
1795174711 76
1795174716 76
1795174721 76
```
</details>

---

