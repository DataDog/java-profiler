---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:31:41 EDT

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
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (5 unique values: 25-34 cores)</summary>

```
1786390105 34
1786390110 34
1786390115 34
1786390120 34
1786390125 34
1786390130 34
1786390135 34
1786390140 34
1786390145 34
1786390150 34
1786390155 34
1786390160 34
1786390165 33
1786390170 33
1786390175 33
1786390180 33
1786390185 33
1786390190 33
1786390195 33
1786390200 29
```
</details>

---

