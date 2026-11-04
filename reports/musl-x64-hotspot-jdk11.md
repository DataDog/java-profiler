---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 952 |
| Sample Rate | 15.87/sec |
| Health Score | 992% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 58-77 cores)</summary>

```
1793812796 74
1793812801 74
1793812806 77
1793812811 77
1793812816 77
1793812821 77
1793812826 77
1793812831 77
1793812836 60
1793812841 60
1793812846 60
1793812851 60
1793812856 60
1793812861 60
1793812866 60
1793812871 60
1793812877 60
1793812882 60
1793812887 60
1793812892 58
```
</details>

---

