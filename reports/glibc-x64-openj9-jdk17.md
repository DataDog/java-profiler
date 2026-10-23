---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 19:01:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 43-69 cores)</summary>

```
1792796187 69
1792796192 69
1792796197 69
1792796202 69
1792796207 69
1792796212 69
1792796217 69
1792796222 69
1792796227 69
1792796232 45
1792796237 45
1792796242 43
1792796247 43
1792796252 43
1792796257 43
1792796262 43
1792796267 43
1792796272 43
1792796277 43
1792796282 45
```
</details>

---

