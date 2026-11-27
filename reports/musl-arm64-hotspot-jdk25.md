---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:54:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1795798255 52
1795798260 52
1795798265 52
1795798270 52
1795798275 52
1795798280 52
1795798285 52
1795798290 52
1795798295 52
1795798300 52
1795798305 52
1795798310 52
1795798315 52
1795798320 52
1795798325 52
1795798330 52
1795798335 52
1795798340 52
1795798345 52
1795798350 64
```
</details>

---

