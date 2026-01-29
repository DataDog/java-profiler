---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ❌ FAIL

**Date:** 2026-01-29 05:23:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 21 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769681908 24
1769681913 24
1769681918 24
1769681923 24
1769681928 24
1769681933 24
1769681938 24
1769681943 24
1769681948 24
1769681953 24
1769681958 24
1769681963 24
1769681968 24
1769681973 24
1769681978 24
1769681983 24
1769681988 24
1769681993 24
1769681998 24
1769682003 24
```
</details>

---

