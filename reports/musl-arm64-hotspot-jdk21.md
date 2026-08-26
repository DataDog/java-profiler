---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-26 10:30:27 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1787754299 52
1787754304 52
1787754309 52
1787754314 52
1787754319 52
1787754324 52
1787754329 50
1787754335 50
1787754340 50
1787754345 50
1787754350 50
1787754355 50
1787754360 50
1787754365 50
1787754370 50
1787754375 50
1787754380 50
1787754385 50
1787754390 50
1787754395 50
```
</details>

---

