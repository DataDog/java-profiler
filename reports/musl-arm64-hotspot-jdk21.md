---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 08:08:21 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 8 |
| Allocations | 133 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 27-64 cores)</summary>

```
1789992199 27
1789992204 27
1789992209 27
1789992214 27
1789992219 27
1789992224 27
1789992229 27
1789992234 64
1789992239 64
1789992244 49
1789992249 49
1789992254 49
1789992259 49
1789992264 49
1789992269 49
1789992274 49
1789992279 49
1789992284 49
1789992289 49
1789992294 49
```
</details>

---

