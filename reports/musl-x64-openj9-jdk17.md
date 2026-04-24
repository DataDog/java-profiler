---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:33:46 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 12 |
| Allocations | 176 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 12 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (7 unique values: 71-92 cores)</summary>

```
1777033830 71
1777033835 71
1777033840 71
1777033845 71
1777033850 71
1777033855 92
1777033860 92
1777033865 92
1777033870 92
1777033875 87
1777033880 87
1777033885 87
1777033890 89
1777033895 89
1777033900 89
1777033905 89
1777033910 89
1777033915 91
1777033920 91
1777033925 91
```
</details>

---

