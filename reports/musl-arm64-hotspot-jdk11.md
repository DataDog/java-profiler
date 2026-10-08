---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:53:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 9 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791470868 48
1791470873 48
1791470878 48
1791470883 48
1791470888 48
1791470893 48
1791470898 48
1791470904 48
1791470909 48
1791470914 48
1791470919 48
1791470924 48
1791470929 48
1791470934 48
1791470939 48
1791470944 48
1791470949 48
1791470954 43
1791470959 43
1791470964 43
```
</details>

---

