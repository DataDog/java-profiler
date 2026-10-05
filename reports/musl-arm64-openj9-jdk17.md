---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 00:55:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 10 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791175917 51
1791175922 51
1791175927 51
1791175932 51
1791175937 51
1791175942 51
1791175947 64
1791175952 64
1791175957 64
1791175962 64
1791175967 64
1791175972 64
1791175977 64
1791175982 64
1791175987 64
1791175992 64
1791175997 64
1791176002 64
1791176007 64
1791176012 64
```
</details>

---

