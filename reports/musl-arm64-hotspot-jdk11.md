---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:20:31 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795796221 42
1795796226 42
1795796231 42
1795796236 42
1795796241 42
1795796246 42
1795796251 42
1795796256 42
1795796261 42
1795796266 42
1795796271 47
1795796276 47
1795796281 47
1795796286 47
1795796291 47
1795796296 47
1795796301 47
1795796306 47
1795796311 47
1795796316 47
```
</details>

---

