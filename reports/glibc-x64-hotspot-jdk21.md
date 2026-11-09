---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 09:27:55 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794234169 27
1794234174 27
1794234179 27
1794234184 27
1794234189 27
1794234194 29
1794234199 29
1794234204 29
1794234209 29
1794234214 29
1794234219 29
1794234224 29
1794234229 29
1794234234 29
1794234239 29
1794234244 29
1794234249 29
1794234254 29
1794234259 29
1794234264 29
```
</details>

---

