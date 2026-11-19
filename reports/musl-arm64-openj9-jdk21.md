---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:35:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795112734 50
1795112739 50
1795112744 50
1795112749 50
1795112754 50
1795112759 50
1795112764 50
1795112769 50
1795112774 50
1795112779 50
1795112784 50
1795112790 50
1795112795 50
1795112800 50
1795112805 50
1795112810 50
1795112815 50
1795112820 50
1795112825 50
1795112830 50
```
</details>

---

