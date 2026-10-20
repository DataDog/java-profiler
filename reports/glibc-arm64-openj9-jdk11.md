---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 14:20:47 EDT

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
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792519995 48
1792520000 48
1792520005 48
1792520010 48
1792520015 48
1792520020 48
1792520025 48
1792520030 48
1792520035 48
1792520040 43
1792520045 43
1792520050 43
1792520055 43
1792520060 43
1792520065 43
1792520071 43
1792520076 43
1792520081 43
1792520086 43
1792520091 43
```
</details>

---

