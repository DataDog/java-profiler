---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 10 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1786018989 64
1786018994 64
1786018999 64
1786019004 64
1786019009 64
1786019014 64
1786019019 53
1786019024 53
1786019029 53
1786019034 53
1786019039 53
1786019044 53
1786019049 53
1786019054 53
1786019059 53
1786019064 53
1786019069 53
1786019074 53
1786019079 53
1786019084 53
```
</details>

---

