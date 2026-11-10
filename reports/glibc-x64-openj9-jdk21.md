---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:42:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 852 |
| Sample Rate | 14.20/sec |
| Health Score | 887% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 40-78 cores)</summary>

```
1794325009 78
1794325014 78
1794325019 78
1794325024 78
1794325029 78
1794325034 78
1794325039 78
1794325044 78
1794325049 63
1794325054 63
1794325059 63
1794325064 65
1794325069 65
1794325074 65
1794325079 65
1794325084 65
1794325089 65
1794325094 65
1794325099 65
1794325104 40
```
</details>

---

