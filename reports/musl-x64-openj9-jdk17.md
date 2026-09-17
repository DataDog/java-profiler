---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:33:14 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 49-75 cores)</summary>

```
1789680172 73
1789680177 73
1789680182 75
1789680187 75
1789680192 75
1789680197 71
1789680202 71
1789680207 71
1789680212 71
1789680217 73
1789680222 73
1789680227 53
1789680232 53
1789680237 53
1789680242 53
1789680247 53
1789680252 53
1789680257 49
1789680262 49
1789680267 49
```
</details>

---

