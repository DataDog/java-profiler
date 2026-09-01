---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 12:13:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788278940 64
1788278945 64
1788278950 64
1788278955 64
1788278960 64
1788278965 64
1788278970 64
1788278975 64
1788278980 64
1788278985 64
1788278990 64
1788278995 64
1788279000 64
1788279005 64
1788279010 64
1788279015 64
1788279020 64
1788279025 59
1788279030 59
1788279035 59
```
</details>

---

