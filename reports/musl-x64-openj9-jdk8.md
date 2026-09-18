---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 04:34:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1789719887 42
1789719892 42
1789719897 42
1789719902 42
1789719907 42
1789719912 40
1789719917 40
1789719922 40
1789719927 40
1789719932 40
1789719937 40
1789719942 40
1789719947 42
1789719952 42
1789719957 42
1789719962 42
1789719967 42
1789719972 42
1789719977 42
1789719982 42
```
</details>

---

