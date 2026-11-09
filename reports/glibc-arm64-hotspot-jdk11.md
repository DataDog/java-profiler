---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 09:27:54 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (4 unique values: 41-46 cores)</summary>

```
1794234148 46
1794234153 46
1794234158 46
1794234163 46
1794234168 46
1794234173 41
1794234178 41
1794234183 41
1794234188 41
1794234193 41
1794234198 43
1794234204 43
1794234209 41
1794234214 41
1794234219 41
1794234224 41
1794234229 44
1794234234 44
1794234239 44
1794234244 44
```
</details>

---

