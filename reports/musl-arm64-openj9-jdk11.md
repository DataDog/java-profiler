---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:12 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 9 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789719892 46
1789719897 46
1789719902 46
1789719907 46
1789719912 48
1789719917 48
1789719922 48
1789719927 48
1789719932 48
1789719937 48
1789719942 48
1789719947 48
1789719952 48
1789719957 48
1789719962 48
1789719967 48
1789719973 48
1789719978 48
1789719983 48
1789719988 48
```
</details>

---

