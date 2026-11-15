---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-14 19:51:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 47-80 cores)</summary>

```
1794703599 47
1794703604 47
1794703609 47
1794703614 47
1794703619 47
1794703624 80
1794703629 80
1794703634 80
1794703639 80
1794703644 80
1794703649 80
1794703654 80
1794703659 80
1794703664 80
1794703669 80
1794703674 80
1794703679 80
1794703684 80
1794703689 80
1794703694 80
```
</details>

---

