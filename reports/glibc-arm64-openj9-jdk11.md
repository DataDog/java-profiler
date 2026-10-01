---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:20:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 334 |
| Sample Rate | 5.57/sec |
| Health Score | 348% |
| Threads | 13 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790853411 43
1790853416 43
1790853421 43
1790853426 43
1790853431 43
1790853436 43
1790853441 43
1790853446 43
1790853451 43
1790853456 48
1790853461 48
1790853466 43
1790853471 43
1790853476 43
1790853481 43
1790853487 43
1790853492 43
1790853497 43
1790853502 43
1790853507 43
```
</details>

---

