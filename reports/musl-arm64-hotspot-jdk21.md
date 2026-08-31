---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:21:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 11 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788138982 43
1788138987 43
1788138992 43
1788138997 43
1788139002 43
1788139007 43
1788139012 43
1788139017 48
1788139022 48
1788139027 48
1788139032 48
1788139037 48
1788139042 48
1788139047 48
1788139052 48
1788139057 48
1788139062 48
1788139067 48
1788139072 48
1788139077 48
```
</details>

---

