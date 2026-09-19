---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-19 05:47:39 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 11 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789810999 38
1789811004 38
1789811009 38
1789811014 43
1789811019 43
1789811024 43
1789811029 43
1789811034 43
1789811039 43
1789811044 43
1789811049 43
1789811054 43
1789811059 43
1789811064 43
1789811069 43
1789811074 43
1789811079 43
1789811084 43
1789811089 43
1789811094 43
```
</details>

---

