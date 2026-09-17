---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:27:27 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789680066 32
1789680071 32
1789680076 32
1789680081 32
1789680086 32
1789680091 30
1789680096 30
1789680101 30
1789680106 30
1789680111 30
1789680116 30
1789680121 30
1789680126 32
1789680131 32
1789680136 32
1789680141 32
1789680146 32
1789680151 32
1789680156 32
1789680161 32
```
</details>

---

