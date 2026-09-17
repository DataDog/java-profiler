---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 10:30:05 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 19 |
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
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 19-27 cores)</summary>

```
1789655059 25
1789655064 25
1789655069 25
1789655074 25
1789655079 25
1789655084 25
1789655089 25
1789655094 27
1789655099 27
1789655104 27
1789655109 19
1789655114 19
1789655119 19
1789655124 19
1789655129 19
1789655134 19
1789655139 19
1789655144 19
1789655149 19
1789655154 19
```
</details>

---

