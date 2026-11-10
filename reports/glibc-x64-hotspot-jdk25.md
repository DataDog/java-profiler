---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:29:43 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 17-32 cores)</summary>

```
1794324153 30
1794324158 32
1794324163 32
1794324168 32
1794324173 32
1794324178 32
1794324183 32
1794324188 32
1794324193 32
1794324198 32
1794324203 27
1794324208 27
1794324213 27
1794324218 27
1794324223 27
1794324228 27
1794324233 27
1794324238 27
1794324243 27
1794324248 27
```
</details>

---

