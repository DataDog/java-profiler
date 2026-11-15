---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:02:47 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1030 |
| Sample Rate | 17.17/sec |
| Health Score | 1073% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1794783556 66
1794783561 66
1794783566 66
1794783571 66
1794783576 66
1794783581 66
1794783586 66
1794783591 64
1794783596 64
1794783601 64
1794783606 64
1794783611 64
1794783616 64
1794783621 64
1794783626 64
1794783631 64
1794783636 64
1794783641 64
1794783646 64
1794783651 64
```
</details>

---

