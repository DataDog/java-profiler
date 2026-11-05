---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:29 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1793895008 79
1793895013 79
1793895018 79
1793895023 79
1793895028 79
1793895033 79
1793895038 79
1793895043 79
1793895048 79
1793895053 79
1793895058 79
1793895063 81
1793895068 81
1793895073 81
1793895078 81
1793895083 81
1793895088 81
1793895093 81
1793895098 81
1793895103 81
```
</details>

---

