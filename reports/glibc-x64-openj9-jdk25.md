---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 09:58:43 EDT

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
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 47-59 cores)</summary>

```
1791986098 59
1791986103 59
1791986108 59
1791986113 59
1791986118 59
1791986123 59
1791986128 59
1791986133 59
1791986138 57
1791986143 57
1791986148 55
1791986153 55
1791986158 55
1791986163 55
1791986168 55
1791986173 55
1791986178 55
1791986183 55
1791986188 55
1791986193 47
```
</details>

---

