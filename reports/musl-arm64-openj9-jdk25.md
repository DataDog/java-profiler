---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:13:47 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1788278918 25
1788278923 25
1788278928 25
1788278933 20
1788278938 20
1788278943 20
1788278948 20
1788278953 20
1788278958 20
1788278963 20
1788278968 20
1788278973 20
1788278978 20
1788278983 20
1788278988 20
1788278993 20
1788278998 20
1788279003 20
1788279008 20
1788279013 20
```
</details>

---

