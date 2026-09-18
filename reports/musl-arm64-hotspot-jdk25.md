---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:48:05 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789731820 30
1789731825 30
1789731830 30
1789731835 30
1789731840 25
1789731845 25
1789731850 25
1789731855 25
1789731860 25
1789731865 25
1789731870 25
1789731875 25
1789731880 25
1789731885 25
1789731890 25
1789731895 25
1789731900 30
1789731905 30
1789731910 30
1789731915 30
```
</details>

---

