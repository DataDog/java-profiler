---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 05:47:57 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795344198 34
1795344203 34
1795344208 34
1795344213 34
1795344218 34
1795344223 34
1795344228 34
1795344233 34
1795344239 34
1795344244 34
1795344249 34
1795344254 34
1795344259 34
1795344264 34
1795344269 34
1795344274 34
1795344279 34
1795344284 32
1795344289 32
1795344294 32
```
</details>

---

