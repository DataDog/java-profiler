---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 12:33:20 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 12-24 cores)</summary>

```
1791476921 12
1791476926 12
1791476931 12
1791476936 12
1791476941 12
1791476946 12
1791476951 12
1791476956 12
1791476961 12
1791476966 12
1791476971 12
1791476976 12
1791476981 12
1791476986 12
1791476991 12
1791476996 12
1791477001 12
1791477006 12
1791477011 12
1791477016 12
```
</details>

---

