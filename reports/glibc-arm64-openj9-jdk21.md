---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:48:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793187923 48
1793187928 48
1793187933 48
1793187938 48
1793187943 48
1793187948 48
1793187953 48
1793187958 48
1793187963 48
1793187968 48
1793187973 48
1793187978 48
1793187983 48
1793187988 43
1793187993 43
1793187998 43
1793188003 43
1793188008 43
1793188013 43
1793188018 43
```
</details>

---

