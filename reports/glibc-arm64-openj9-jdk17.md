---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 10:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1789655064 30
1789655069 30
1789655074 30
1789655079 30
1789655084 30
1789655089 30
1789655094 30
1789655099 30
1789655104 30
1789655109 30
1789655114 30
1789655119 30
1789655125 30
1789655130 30
1789655135 30
1789655140 30
1789655145 30
1789655150 10
1789655155 10
1789655160 10
```
</details>

---

