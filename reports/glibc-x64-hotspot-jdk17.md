---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:37:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 65-70 cores)</summary>

```
1794508159 70
1794508164 65
1794508169 65
1794508174 65
1794508179 65
1794508184 65
1794508189 65
1794508194 65
1794508199 65
1794508204 65
1794508209 65
1794508214 65
1794508219 65
1794508224 68
1794508229 68
1794508234 68
1794508239 68
1794508244 68
1794508249 68
1794508254 68
```
</details>

---

