---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 10:11:27 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786457182 32
1786457187 32
1786457192 32
1786457197 32
1786457202 32
1786457207 32
1786457212 32
1786457217 32
1786457222 32
1786457227 32
1786457232 32
1786457237 32
1786457242 32
1786457247 32
1786457252 32
1786457257 32
1786457262 32
1786457267 32
1786457272 32
1786457277 32
```
</details>

---

