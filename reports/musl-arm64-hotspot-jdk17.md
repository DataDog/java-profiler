---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1795014935 38
1795014940 38
1795014945 38
1795014950 38
1795014955 38
1795014960 38
1795014965 38
1795014970 38
1795014975 38
1795014980 38
1795014985 38
1795014990 38
1795014995 43
1795015000 43
1795015005 43
1795015010 43
1795015015 43
1795015020 43
1795015025 43
1795015030 43
```
</details>

---

