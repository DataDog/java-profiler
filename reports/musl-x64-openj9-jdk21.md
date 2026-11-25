---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:28:14 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 43-59 cores)</summary>

```
1795641755 59
1795641760 59
1795641765 59
1795641770 59
1795641775 59
1795641780 59
1795641785 59
1795641790 59
1795641795 59
1795641800 59
1795641805 59
1795641810 59
1795641815 59
1795641820 59
1795641825 59
1795641830 59
1795641835 59
1795641840 59
1795641845 59
1795641850 45
```
</details>

---

