---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 10:30:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (3 unique values: 31-34 cores)</summary>

```
1789655049 31
1789655054 31
1789655059 31
1789655064 31
1789655069 31
1789655074 31
1789655079 31
1789655084 31
1789655089 31
1789655094 31
1789655099 31
1789655104 31
1789655109 31
1789655114 33
1789655119 33
1789655124 33
1789655129 33
1789655134 31
1789655139 31
1789655144 31
```
</details>

---

