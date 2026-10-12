---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-12 05:09:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 11 |
| Allocations | 108 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 31-38 cores)</summary>

```
1791795888 38
1791795893 38
1791795898 38
1791795903 38
1791795908 38
1791795913 38
1791795918 33
1791795923 33
1791795928 33
1791795933 33
1791795938 33
1791795943 33
1791795948 38
1791795953 38
1791795958 36
1791795963 36
1791795968 31
1791795973 31
1791795978 36
1791795983 36
```
</details>

---

