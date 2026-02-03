---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 07:41:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 25-32 cores)</summary>

```
1770122123 32
1770122128 32
1770122133 30
1770122138 30
1770122143 27
1770122148 27
1770122153 26
1770122158 26
1770122163 25
1770122168 25
1770122173 27
1770122178 27
1770122183 27
1770122188 27
1770122193 25
1770122198 25
1770122203 25
1770122208 25
1770122213 25
1770122218 25
```
</details>

---

