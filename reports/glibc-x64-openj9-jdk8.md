---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 12:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 73-75 cores)</summary>

```
1793812796 75
1793812801 75
1793812806 75
1793812811 75
1793812816 75
1793812821 75
1793812826 75
1793812831 75
1793812836 75
1793812841 73
1793812846 73
1793812851 73
1793812856 73
1793812861 73
1793812866 73
1793812871 73
1793812876 73
1793812881 73
1793812886 73
1793812891 73
```
</details>

---

