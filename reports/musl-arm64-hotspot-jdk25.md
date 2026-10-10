---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-10 05:51:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 10 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791625579 40
1791625584 40
1791625589 40
1791625594 40
1791625599 40
1791625604 40
1791625609 40
1791625614 40
1791625619 40
1791625624 40
1791625630 40
1791625635 40
1791625640 40
1791625645 40
1791625650 40
1791625655 40
1791625660 40
1791625665 40
1791625670 40
1791625675 40
```
</details>

---

