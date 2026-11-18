---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 07:14:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 46-83 cores)</summary>

```
1795003810 55
1795003815 55
1795003820 55
1795003825 55
1795003830 55
1795003836 57
1795003841 57
1795003846 57
1795003851 57
1795003856 57
1795003861 55
1795003866 55
1795003871 55
1795003876 55
1795003881 46
1795003886 46
1795003891 63
1795003896 63
1795003901 83
1795003906 83
```
</details>

---

