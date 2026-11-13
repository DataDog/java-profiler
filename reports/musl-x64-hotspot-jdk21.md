---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:24:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 24-30 cores)</summary>

```
1794594012 30
1794594017 30
1794594022 28
1794594027 28
1794594032 28
1794594037 28
1794594042 28
1794594047 28
1794594052 28
1794594057 28
1794594062 28
1794594067 28
1794594072 28
1794594077 30
1794594082 30
1794594087 30
1794594092 30
1794594097 30
1794594102 30
1794594107 24
```
</details>

---

