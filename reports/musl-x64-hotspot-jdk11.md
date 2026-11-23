---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:31:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795397179 72
1795397184 72
1795397189 72
1795397194 72
1795397199 72
1795397204 70
1795397209 70
1795397214 70
1795397219 70
1795397224 70
1795397229 70
1795397234 70
1795397239 70
1795397244 70
1795397249 70
1795397254 72
1795397259 72
1795397264 72
1795397269 72
1795397275 72
```
</details>

---

