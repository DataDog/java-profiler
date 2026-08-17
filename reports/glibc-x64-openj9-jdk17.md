---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-08-17 14:25:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (1 unique values: 88-88 cores)</summary>

```
1786990945 88
1786990950 88
1786990955 88
1786990960 88
1786990965 88
1786990970 88
1786990975 88
1786990980 88
1786990985 88
1786990990 88
1786990995 88
1786991000 88
1786991005 88
1786991010 88
1786991015 88
1786991020 88
1786991025 88
1786991030 88
1786991035 88
1786991040 88
```
</details>

---

