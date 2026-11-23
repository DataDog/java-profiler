---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:31:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (6 unique values: 23-57 cores)</summary>

```
1795397186 57
1795397192 57
1795397197 55
1795397202 55
1795397207 38
1795397212 38
1795397217 36
1795397222 36
1795397227 36
1795397232 36
1795397237 36
1795397242 36
1795397247 36
1795397252 36
1795397257 38
1795397262 38
1795397267 40
1795397272 40
1795397277 40
1795397282 40
```
</details>

---

