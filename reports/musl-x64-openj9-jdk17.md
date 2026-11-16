---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:15:48 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 69-79 cores)</summary>

```
1794841825 69
1794841830 69
1794841835 69
1794841840 69
1794841845 69
1794841850 69
1794841855 69
1794841860 69
1794841865 69
1794841870 69
1794841875 69
1794841880 77
1794841885 77
1794841890 77
1794841895 77
1794841900 77
1794841905 77
1794841910 77
1794841915 77
1794841920 77
```
</details>

---

