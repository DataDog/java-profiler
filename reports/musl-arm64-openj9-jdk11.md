---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 11:26:16 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1792163982 44
1792163987 44
1792163992 44
1792163998 46
1792164003 46
1792164008 46
1792164013 46
1792164018 46
1792164023 46
1792164028 46
1792164033 46
1792164038 46
1792164043 46
1792164048 46
1792164053 46
1792164058 46
1792164063 46
1792164068 46
1792164073 46
1792164078 46
```
</details>

---

