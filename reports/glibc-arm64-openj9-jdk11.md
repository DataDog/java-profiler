---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:52:38 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 21-26 cores)</summary>

```
1791279970 26
1791279975 26
1791279980 26
1791279985 26
1791279990 26
1791279995 26
1791280000 26
1791280005 26
1791280010 26
1791280015 21
1791280020 21
1791280025 21
1791280030 21
1791280035 21
1791280040 21
1791280045 21
1791280050 21
1791280055 21
1791280060 21
1791280065 21
```
</details>

---

