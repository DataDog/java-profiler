---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:46:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 50-59 cores)</summary>

```
1795632052 59
1795632057 59
1795632062 59
1795632067 59
1795632072 59
1795632077 59
1795632082 59
1795632087 59
1795632092 59
1795632097 59
1795632102 59
1795632107 59
1795632112 59
1795632117 59
1795632122 59
1795632127 59
1795632132 59
1795632137 50
1795632142 50
1795632147 50
```
</details>

---

