---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 10:58:56 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 101 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787151245 43
1787151250 43
1787151255 43
1787151260 43
1787151265 43
1787151270 43
1787151275 43
1787151280 43
1787151285 48
1787151290 48
1787151295 48
1787151300 48
1787151305 48
1787151310 48
1787151315 48
1787151320 48
1787151325 48
1787151330 48
1787151335 48
1787151340 48
```
</details>

---

