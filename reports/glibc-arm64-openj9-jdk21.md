---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:13:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795194514 50
1795194519 50
1795194524 50
1795194529 50
1795194534 50
1795194539 50
1795194544 50
1795194549 50
1795194554 50
1795194559 50
1795194564 50
1795194569 50
1795194574 50
1795194579 45
1795194584 45
1795194589 45
1795194594 45
1795194599 45
1795194604 45
1795194609 45
```
</details>

---

