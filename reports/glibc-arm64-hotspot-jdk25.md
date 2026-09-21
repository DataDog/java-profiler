---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 05:49:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 41-49 cores)</summary>

```
1789983860 41
1789983865 41
1789983870 49
1789983875 49
1789983880 49
1789983885 49
1789983890 49
1789983895 49
1789983900 49
1789983905 49
1789983910 49
1789983915 49
1789983920 49
1789983925 49
1789983930 49
1789983935 49
1789983940 49
1789983945 49
1789983950 49
1789983955 49
```
</details>

---

