---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:59:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793148944 48
1793148949 48
1793148954 48
1793148959 48
1793148964 48
1793148969 48
1793148974 48
1793148979 48
1793148984 48
1793148989 48
1793148994 48
1793148999 48
1793149004 48
1793149009 43
1793149014 43
1793149019 43
1793149024 43
1793149029 43
1793149034 43
1793149039 43
```
</details>

---

