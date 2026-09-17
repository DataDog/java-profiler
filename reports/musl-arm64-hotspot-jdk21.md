---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 14:20:09 EDT

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
| CPU Cores (start) | 6 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 6-26 cores)</summary>

```
1789668953 6
1789668958 6
1789668963 6
1789668968 26
1789668973 26
1789668978 26
1789668983 26
1789668988 26
1789668993 26
1789668998 26
1789669003 26
1789669008 26
1789669013 26
1789669018 26
1789669023 26
1789669028 26
1789669033 26
1789669038 26
1789669043 26
1789669048 26
```
</details>

---

