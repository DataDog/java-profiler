---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 20:52:53 EDT

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
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1778546970 64
1778546975 64
1778546980 64
1778546985 64
1778546990 64
1778546995 64
1778547000 64
1778547005 64
1778547010 64
1778547015 64
1778547020 64
1778547025 64
1778547030 64
1778547035 64
1778547040 64
1778547045 64
1778547050 64
1778547055 64
1778547060 64
1778547065 64
```
</details>

---

