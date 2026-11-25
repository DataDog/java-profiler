---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1795641198 32
1795641203 30
1795641208 30
1795641213 30
1795641218 30
1795641223 30
1795641228 30
1795641234 30
1795641239 30
1795641244 30
1795641249 30
1795641254 30
1795641259 30
1795641264 30
1795641269 30
1795641274 30
1795641279 30
1795641284 30
1795641289 30
1795641294 30
```
</details>

---

