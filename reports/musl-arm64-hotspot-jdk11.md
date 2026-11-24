---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:13:31 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 9 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (4 unique values: 44-59 cores)</summary>

```
1795529213 54
1795529218 49
1795529223 49
1795529228 49
1795529233 49
1795529238 44
1795529243 44
1795529248 44
1795529253 44
1795529258 44
1795529263 44
1795529268 44
1795529273 44
1795529278 44
1795529283 44
1795529288 44
1795529293 54
1795529298 54
1795529304 54
1795529309 54
```
</details>

---

