---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 10:29:18 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1792678969 64
1792678974 64
1792678979 64
1792678984 64
1792678989 64
1792678994 64
1792678999 64
1792679004 64
1792679009 64
1792679014 47
1792679019 47
1792679024 47
1792679029 47
1792679034 47
1792679039 47
1792679044 47
1792679049 47
1792679054 47
1792679059 47
1792679064 47
```
</details>

---

