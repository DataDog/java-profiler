---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 06:12:56 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 54-76 cores)</summary>

```
1795172855 76
1795172860 76
1795172865 76
1795172870 76
1795172875 76
1795172880 76
1795172885 76
1795172890 76
1795172895 76
1795172900 76
1795172905 76
1795172910 76
1795172915 76
1795172920 56
1795172925 56
1795172930 54
1795172935 54
1795172940 54
1795172945 71
1795172950 71
```
</details>

---

