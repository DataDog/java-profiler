---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 06:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 71-76 cores)</summary>

```
1793271019 71
1793271024 76
1793271029 76
1793271034 76
1793271039 76
1793271044 76
1793271049 76
1793271054 76
1793271059 76
1793271064 76
1793271069 76
1793271074 76
1793271079 76
1793271084 76
1793271089 76
1793271094 76
1793271099 76
1793271104 76
1793271109 76
1793271114 76
```
</details>

---

