---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 07:41:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 11 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 13 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1770122143 51
1770122148 51
1770122153 51
1770122158 51
1770122163 51
1770122168 51
1770122173 51
1770122178 51
1770122183 51
1770122188 51
1770122193 51
1770122198 51
1770122204 51
1770122209 51
1770122214 51
1770122219 55
1770122224 55
1770122229 55
1770122234 55
1770122239 55
```
</details>

---

