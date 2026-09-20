---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-20 05:46:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 927 |
| Sample Rate | 15.45/sec |
| Health Score | 966% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1789897345 29
1789897350 29
1789897355 29
1789897360 29
1789897365 29
1789897370 29
1789897375 29
1789897380 29
1789897385 29
1789897390 29
1789897395 29
1789897400 29
1789897405 29
1789897410 29
1789897415 34
1789897420 34
1789897425 34
1789897430 34
1789897435 34
1789897440 34
```
</details>

---

