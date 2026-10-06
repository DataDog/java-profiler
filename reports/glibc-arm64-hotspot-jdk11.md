---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 12:01:34 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1791301984 41
1791301989 41
1791301994 41
1791301999 41
1791302004 41
1791302009 41
1791302014 41
1791302019 41
1791302024 41
1791302029 41
1791302034 41
1791302039 41
1791302044 41
1791302049 41
1791302054 41
1791302059 41
1791302064 41
1791302069 41
1791302074 41
1791302079 41
```
</details>

---

