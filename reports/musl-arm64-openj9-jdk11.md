---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 10:44:06 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1790779138 53
1790779143 53
1790779148 53
1790779153 53
1790779158 53
1790779163 53
1790779168 53
1790779173 53
1790779178 53
1790779183 53
1790779188 53
1790779193 53
1790779198 53
1790779203 53
1790779208 53
1790779213 53
1790779218 53
1790779223 53
1790779228 53
1790779233 53
```
</details>

---

