---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 00:55:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 7 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1792990180 79
1792990185 96
1792990190 96
1792990195 96
1792990200 96
1792990205 96
1792990210 96
1792990215 81
1792990220 81
1792990225 81
1792990230 81
1792990235 79
1792990240 79
1792990245 79
1792990250 79
1792990255 79
1792990260 79
1792990265 81
1792990270 81
1792990275 81
```
</details>

---

