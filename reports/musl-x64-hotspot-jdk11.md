---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 10:29:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 69-90 cores)</summary>

```
1792678964 69
1792678969 69
1792678974 69
1792678979 69
1792678984 69
1792678989 69
1792678994 69
1792678999 69
1792679004 90
1792679009 90
1792679014 90
1792679019 90
1792679024 90
1792679029 90
1792679034 90
1792679039 90
1792679044 90
1792679049 90
1792679054 90
1792679059 90
```
</details>

---

