---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 10:39:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1789741922 43
1789741927 43
1789741932 43
1789741937 42
1789741942 42
1789741947 42
1789741952 42
1789741957 42
1789741962 42
1789741967 43
1789741972 43
1789741977 43
1789741982 43
1789741987 48
1789741992 48
1789741997 48
1789742002 48
1789742007 48
1789742012 48
1789742017 48
```
</details>

---

