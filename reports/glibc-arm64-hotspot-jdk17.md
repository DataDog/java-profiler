---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 10:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1789655059 10
1789655064 10
1789655069 10
1789655074 10
1789655079 10
1789655084 10
1789655089 10
1789655094 10
1789655099 10
1789655104 10
1789655109 10
1789655114 10
1789655119 10
1789655124 10
1789655129 10
1789655134 10
1789655139 10
1789655144 10
1789655149 10
1789655154 10
```
</details>

---

