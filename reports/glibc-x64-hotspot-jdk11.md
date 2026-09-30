---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1790763111 13
1790763116 13
1790763121 13
1790763126 13
1790763131 13
1790763136 13
1790763141 13
1790763146 15
1790763151 15
1790763157 15
1790763162 15
1790763167 15
1790763172 15
1790763177 15
1790763182 15
1790763187 15
1790763192 15
1790763197 15
1790763202 15
1790763207 15
```
</details>

---

