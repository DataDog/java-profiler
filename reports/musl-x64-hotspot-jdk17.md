---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 08:40:37 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1789734953 74
1789734958 74
1789734963 74
1789734968 74
1789734974 74
1789734979 74
1789734984 74
1789734989 74
1789734994 72
1789734999 72
1789735004 72
1789735009 72
1789735014 72
1789735019 72
1789735024 72
1789735030 72
1789735035 72
1789735040 72
1789735045 72
1789735050 72
```
</details>

---

