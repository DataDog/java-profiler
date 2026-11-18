---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 41-59 cores)</summary>

```
1795027795 43
1795027800 43
1795027805 43
1795027810 43
1795027815 41
1795027820 41
1795027825 41
1795027830 46
1795027835 46
1795027840 59
1795027845 59
1795027850 59
1795027855 59
1795027860 59
1795027865 59
1795027870 59
1795027875 59
1795027880 59
1795027885 59
1795027890 59
```
</details>

---

