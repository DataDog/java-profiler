---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-21 08:20:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 75-96 cores)</summary>

```
1792584865 75
1792584870 75
1792584875 75
1792584880 75
1792584885 75
1792584890 96
1792584896 96
1792584901 96
1792584906 75
1792584911 75
1792584916 75
1792584921 75
1792584926 75
1792584931 75
1792584936 75
1792584941 75
1792584946 75
1792584951 75
1792584956 75
1792584961 75
```
</details>

---

