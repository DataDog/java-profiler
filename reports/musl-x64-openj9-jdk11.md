---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:35:48 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 66-75 cores)</summary>

```
1795112729 68
1795112734 68
1795112739 68
1795112744 68
1795112749 68
1795112754 68
1795112759 66
1795112764 66
1795112769 66
1795112774 66
1795112779 66
1795112784 66
1795112789 66
1795112794 66
1795112799 66
1795112804 66
1795112809 66
1795112814 66
1795112820 66
1795112825 66
```
</details>

---

