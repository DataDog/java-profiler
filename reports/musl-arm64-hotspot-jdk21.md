---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:43:04 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789979899 48
1789979904 48
1789979909 48
1789979914 48
1789979919 48
1789979924 43
1789979929 43
1789979934 43
1789979939 43
1789979944 43
1789979949 38
1789979954 38
1789979959 38
1789979964 38
1789979969 38
1789979974 38
1789979979 43
1789979984 43
1789979989 43
1789979994 43
```
</details>

---

