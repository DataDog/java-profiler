---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:53:36 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 972 |
| Sample Rate | 16.20/sec |
| Health Score | 1012% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1778172616 76
1778172621 76
1778172626 76
1778172631 79
1778172636 79
1778172641 79
1778172646 79
1778172651 79
1778172656 79
1778172661 74
1778172666 74
1778172671 74
1778172676 74
1778172681 74
1778172686 74
1778172691 74
1778172696 74
1778172701 74
1778172706 74
1778172711 74
```
</details>

---

