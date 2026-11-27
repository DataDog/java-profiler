---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:54:56 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795798280 64
1795798285 64
1795798290 64
1795798295 64
1795798300 64
1795798305 64
1795798310 64
1795798315 64
1795798320 64
1795798325 64
1795798330 64
1795798335 64
1795798340 64
1795798345 64
1795798350 64
1795798355 64
1795798360 64
1795798365 64
1795798371 64
1795798376 64
```
</details>

---

