---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 11:50:01 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1778514214 60
1778514219 60
1778514224 60
1778514229 60
1778514234 60
1778514240 60
1778514245 60
1778514250 60
1778514255 60
1778514260 64
1778514265 64
1778514270 64
1778514275 64
1778514280 64
1778514285 64
1778514290 64
1778514295 64
1778514300 64
1778514305 64
1778514310 64
```
</details>

---

