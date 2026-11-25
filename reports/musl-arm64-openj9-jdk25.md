---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (6 unique values: 33-64 cores)</summary>

```
1795605504 45
1795605509 45
1795605514 45
1795605519 45
1795605524 44
1795605529 44
1795605534 60
1795605539 60
1795605544 60
1795605549 60
1795605554 60
1795605559 60
1795605564 63
1795605569 63
1795605574 63
1795605579 63
1795605584 64
1795605589 64
1795605594 64
1795605599 64
```
</details>

---

