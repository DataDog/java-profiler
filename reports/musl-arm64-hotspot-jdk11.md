---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 08:57:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1793019093 35
1793019098 35
1793019104 35
1793019109 35
1793019114 35
1793019119 35
1793019124 35
1793019129 35
1793019134 35
1793019139 35
1793019144 35
1793019149 35
1793019154 35
1793019159 48
1793019164 48
1793019169 48
1793019174 48
1793019179 36
1793019184 36
1793019189 36
```
</details>

---

