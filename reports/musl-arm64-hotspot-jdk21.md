---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 18:03:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 9 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 17-48 cores)</summary>

```
1789682162 17
1789682167 17
1789682172 17
1789682177 17
1789682182 17
1789682187 17
1789682192 17
1789682197 17
1789682202 17
1789682207 17
1789682212 17
1789682217 17
1789682222 17
1789682227 17
1789682232 17
1789682237 17
1789682242 17
1789682247 48
1789682252 48
1789682257 48
```
</details>

---

