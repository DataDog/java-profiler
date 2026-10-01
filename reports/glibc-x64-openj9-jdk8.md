---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-01 00:59:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 25-63 cores)</summary>

```
1790830471 25
1790830476 25
1790830481 25
1790830486 25
1790830491 25
1790830496 25
1790830501 25
1790830506 25
1790830511 30
1790830516 30
1790830521 30
1790830526 30
1790830531 30
1790830536 30
1790830541 30
1790830546 30
1790830551 63
1790830556 63
1790830561 63
1790830566 63
```
</details>

---

