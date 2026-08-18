---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-18 09:21:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1787059024 47
1787059029 47
1787059034 47
1787059039 47
1787059044 47
1787059049 47
1787059054 47
1787059059 47
1787059064 47
1787059069 47
1787059074 47
1787059079 47
1787059084 47
1787059089 47
1787059094 47
1787059099 47
1787059104 47
1787059109 47
1787059114 47
1787059119 47
```
</details>

---

