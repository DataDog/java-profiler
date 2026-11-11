---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 345 |
| Sample Rate | 5.75/sec |
| Health Score | 359% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794394998 48
1794395003 48
1794395008 48
1794395013 48
1794395018 48
1794395023 48
1794395028 48
1794395033 48
1794395038 48
1794395043 48
1794395048 48
1794395053 48
1794395058 48
1794395063 48
1794395068 48
1794395073 48
1794395078 48
1794395083 28
1794395088 28
1794395093 28
```
</details>

---

