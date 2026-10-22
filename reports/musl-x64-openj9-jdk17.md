---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792686849 89
1792686854 89
1792686859 89
1792686864 89
1792686869 91
1792686874 91
1792686879 91
1792686884 91
1792686889 91
1792686894 91
1792686900 91
1792686905 91
1792686910 91
1792686915 91
1792686920 91
1792686925 91
1792686930 91
1792686935 91
1792686940 91
1792686945 91
```
</details>

---

