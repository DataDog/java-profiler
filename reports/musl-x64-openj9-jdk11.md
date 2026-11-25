---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:02:42 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 72-81 cores)</summary>

```
1795618599 72
1795618604 72
1795618609 72
1795618614 72
1795618619 72
1795618624 72
1795618629 72
1795618634 72
1795618639 72
1795618644 72
1795618649 72
1795618654 72
1795618659 72
1795618664 72
1795618669 81
1795618674 81
1795618679 81
1795618684 81
1795618689 81
1795618694 81
```
</details>

---

