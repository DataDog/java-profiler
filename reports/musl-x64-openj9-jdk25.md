---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 05:39:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 13 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 68-91 cores)</summary>

```
1770114789 68
1770114794 70
1770114799 70
1770114804 68
1770114809 68
1770114814 70
1770114819 70
1770114824 70
1770114829 70
1770114834 70
1770114840 70
1770114845 70
1770114850 91
1770114855 91
1770114860 91
1770114865 91
1770114870 91
1770114875 91
1770114880 91
1770114885 91
```
</details>

---

