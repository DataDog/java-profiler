---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 10:29:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1792678969 86
1792678974 86
1792678979 86
1792678984 86
1792678989 86
1792678994 86
1792678999 88
1792679004 88
1792679009 88
1792679014 88
1792679019 88
1792679024 88
1792679029 88
1792679034 88
1792679039 90
1792679044 90
1792679049 90
1792679054 90
1792679059 90
1792679064 90
```
</details>

---

