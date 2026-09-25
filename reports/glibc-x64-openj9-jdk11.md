---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 04:45:06 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 44-69 cores)</summary>

```
1790325665 44
1790325670 44
1790325675 44
1790325680 44
1790325685 44
1790325690 44
1790325695 44
1790325700 44
1790325705 44
1790325710 44
1790325715 44
1790325720 44
1790325725 44
1790325730 44
1790325735 44
1790325740 69
1790325745 69
1790325750 46
1790325755 46
1790325760 46
```
</details>

---

