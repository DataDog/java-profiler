---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 38-73 cores)</summary>

```
1791193585 48
1791193590 48
1791193595 48
1791193600 50
1791193605 50
1791193610 73
1791193615 73
1791193620 57
1791193625 57
1791193630 57
1791193635 57
1791193640 57
1791193645 57
1791193650 57
1791193655 57
1791193660 38
1791193665 38
1791193670 38
1791193675 38
1791193680 38
```
</details>

---

