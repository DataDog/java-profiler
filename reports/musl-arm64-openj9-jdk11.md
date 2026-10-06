---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:52:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1791279939 40
1791279944 40
1791279949 40
1791279954 40
1791279959 40
1791279964 40
1791279969 40
1791279974 40
1791279979 40
1791279984 40
1791279989 40
1791279994 40
1791279999 40
1791280004 40
1791280009 40
1791280014 40
1791280019 40
1791280024 40
1791280029 40
1791280034 40
```
</details>

---

