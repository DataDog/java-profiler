---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 11:31:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1795105589 55
1795105594 57
1795105599 57
1795105604 57
1795105609 59
1795105614 59
1795105619 59
1795105624 59
1795105629 59
1795105634 59
1795105639 59
1795105644 59
1795105649 59
1795105654 59
1795105659 59
1795105664 59
1795105669 59
1795105674 59
1795105679 59
1795105684 59
```
</details>

---

