---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:41:43 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 27-34 cores)</summary>

```
1787233020 34
1787233025 34
1787233030 34
1787233035 29
1787233040 29
1787233045 29
1787233050 29
1787233055 29
1787233060 29
1787233065 29
1787233070 29
1787233075 29
1787233080 29
1787233085 29
1787233090 29
1787233095 29
1787233100 29
1787233105 29
1787233110 29
1787233115 27
```
</details>

---

