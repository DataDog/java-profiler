---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 16:29:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1777321157 27
1777321162 27
1777321167 27
1777321172 27
1777321177 27
1777321182 27
1777321187 27
1777321192 27
1777321197 27
1777321202 25
1777321207 25
1777321212 25
1777321217 25
1777321222 25
1777321227 25
1777321232 25
1777321237 25
1777321242 25
1777321247 25
1777321252 25
```
</details>

---

