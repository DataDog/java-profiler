---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:44:08 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 20-24 cores)</summary>

```
1789979854 20
1789979859 22
1789979864 22
1789979869 24
1789979874 24
1789979879 24
1789979884 24
1789979889 24
1789979894 24
1789979899 22
1789979904 22
1789979909 22
1789979914 22
1789979919 22
1789979924 22
1789979929 22
1789979934 22
1789979939 22
1789979944 22
1789979949 22
```
</details>

---

