---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 10:29:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1792678983 59
1792678988 59
1792678993 59
1792678998 59
1792679003 59
1792679008 59
1792679013 61
1792679018 61
1792679023 61
1792679028 61
1792679033 63
1792679038 63
1792679043 63
1792679048 63
1792679053 63
1792679058 63
1792679063 63
1792679068 61
1792679073 61
1792679078 61
```
</details>

---

