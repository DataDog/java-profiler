---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790238929 43
1790238934 43
1790238939 43
1790238944 43
1790238949 43
1790238954 43
1790238959 43
1790238964 43
1790238969 43
1790238974 43
1790238979 43
1790238984 43
1790238989 43
1790238994 43
1790238999 43
1790239004 43
1790239009 48
1790239014 48
1790239019 48
1790239024 48
```
</details>

---

