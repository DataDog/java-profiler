---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 05:53:14 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1787305724 92
1787305729 92
1787305734 92
1787305739 92
1787305744 92
1787305749 92
1787305754 92
1787305759 92
1787305764 92
1787305769 92
1787305774 92
1787305779 90
1787305785 90
1787305790 90
1787305795 90
1787305800 90
1787305805 90
1787305810 90
1787305815 88
1787305820 88
```
</details>

---

