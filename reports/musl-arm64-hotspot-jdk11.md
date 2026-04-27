---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 03:38:44 EDT

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777275233 64
1777275238 64
1777275243 64
1777275248 64
1777275253 64
1777275258 64
1777275263 64
1777275268 64
1777275273 64
1777275278 64
1777275283 64
1777275288 64
1777275293 64
1777275298 64
1777275303 64
1777275308 64
1777275313 64
1777275318 64
1777275323 64
1777275328 64
```
</details>

---

