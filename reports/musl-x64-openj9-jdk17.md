---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 13:24:33 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 67-84 cores)</summary>

```
1791220778 79
1791220783 79
1791220788 67
1791220793 67
1791220798 67
1791220803 67
1791220808 67
1791220813 67
1791220818 67
1791220823 67
1791220828 67
1791220833 67
1791220838 84
1791220843 84
1791220848 84
1791220853 84
1791220858 84
1791220863 84
1791220868 84
1791220873 84
```
</details>

---

