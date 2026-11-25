---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 09:56:26 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795618310 64
1795618315 64
1795618320 64
1795618325 64
1795618330 64
1795618335 64
1795618340 64
1795618345 64
1795618350 64
1795618355 64
1795618360 64
1795618365 64
1795618370 64
1795618375 47
1795618380 47
1795618385 47
1795618390 47
1795618395 47
1795618400 47
1795618405 47
```
</details>

---

