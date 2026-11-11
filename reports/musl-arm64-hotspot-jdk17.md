---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:36:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794357163 48
1794357168 48
1794357173 48
1794357178 48
1794357183 48
1794357188 48
1794357193 48
1794357198 48
1794357203 48
1794357208 43
1794357213 43
1794357218 43
1794357223 43
1794357228 43
1794357233 43
1794357238 43
1794357243 43
1794357248 43
1794357253 43
1794357258 43
```
</details>

---

