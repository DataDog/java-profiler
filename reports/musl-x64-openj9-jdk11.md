---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:42:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (4 unique values: 61-68 cores)</summary>

```
1795174646 61
1795174651 61
1795174656 61
1795174661 61
1795174666 61
1795174671 65
1795174676 65
1795174681 65
1795174686 65
1795174691 65
1795174696 65
1795174701 65
1795174706 65
1795174711 65
1795174716 65
1795174721 65
1795174726 68
1795174731 68
1795174736 68
1795174741 68
```
</details>

---

