---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 07:41:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770122103 27
1770122108 27
1770122113 27
1770122118 27
1770122123 27
1770122128 27
1770122133 32
1770122138 32
1770122143 32
1770122148 32
1770122153 32
1770122158 32
1770122163 32
1770122168 32
1770122173 32
1770122178 32
1770122183 32
1770122188 28
1770122193 28
1770122198 28
```
</details>

---

