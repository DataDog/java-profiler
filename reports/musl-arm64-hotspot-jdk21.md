---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 05:58:42 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1794307931 31
1794307936 31
1794307941 31
1794307946 31
1794307951 43
1794307956 43
1794307961 43
1794307966 43
1794307971 43
1794307976 43
1794307981 43
1794307986 43
1794307991 43
1794307996 43
1794308001 43
1794308006 48
1794308011 48
1794308016 48
1794308021 48
1794308026 48
```
</details>

---

