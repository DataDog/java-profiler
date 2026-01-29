---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 05:23:33 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 21.53/sec |
| Health Score | 1346% |
| Threads | 8 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 17-21 cores)</summary>

```
1769681868 17
1769681873 17
1769681878 17
1769681883 17
1769681888 17
1769681893 17
1769681898 17
1769681903 17
1769681908 17
1769681913 17
1769681918 17
1769681923 17
1769681928 17
1769681933 17
1769681938 17
1769681943 17
1769681948 17
1769681953 21
1769681958 21
1769681963 21
```
</details>

---

