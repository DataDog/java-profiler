---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:29:51 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 20-26 cores)</summary>

```
1795001013 20
1795001018 20
1795001023 20
1795001028 20
1795001033 20
1795001038 20
1795001043 25
1795001048 25
1795001053 25
1795001059 25
1795001064 26
1795001069 26
1795001074 26
1795001079 26
1795001084 26
1795001089 26
1795001094 26
1795001099 26
1795001104 26
1795001109 26
```
</details>

---

