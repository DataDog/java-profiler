---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-15 18:02:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 58-81 cores)</summary>

```
1794783561 58
1794783566 58
1794783571 58
1794783576 58
1794783581 58
1794783586 58
1794783591 58
1794783596 58
1794783601 58
1794783606 58
1794783611 58
1794783616 60
1794783621 60
1794783626 81
1794783631 81
1794783636 81
1794783641 81
1794783646 81
1794783651 81
1794783656 81
```
</details>

---

