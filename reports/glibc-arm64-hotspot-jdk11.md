---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 11:44:34 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 995 |
| Sample Rate | 16.58/sec |
| Health Score | 1036% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1794847128 36
1794847133 36
1794847138 36
1794847143 36
1794847148 36
1794847153 36
1794847158 36
1794847163 36
1794847168 36
1794847173 36
1794847178 36
1794847183 36
1794847188 36
1794847193 36
1794847198 36
1794847203 48
1794847208 48
1794847213 48
1794847218 48
1794847223 48
```
</details>

---

