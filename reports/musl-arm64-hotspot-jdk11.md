---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:31:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795397189 29
1795397194 29
1795397199 29
1795397204 29
1795397209 29
1795397214 29
1795397219 29
1795397224 29
1795397229 29
1795397234 29
1795397239 29
1795397244 34
1795397249 34
1795397254 34
1795397259 34
1795397264 34
1795397269 34
1795397274 31
1795397279 31
1795397284 31
```
</details>

---

