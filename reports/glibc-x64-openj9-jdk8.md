---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-23 16:04:38 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-83 cores)</summary>

```
1792785503 50
1792785508 50
1792785513 50
1792785518 50
1792785523 50
1792785528 50
1792785533 50
1792785538 50
1792785543 50
1792785548 50
1792785553 50
1792785558 83
1792785563 83
1792785568 83
1792785573 83
1792785578 83
1792785583 83
1792785588 83
1792785593 83
1792785598 83
```
</details>

---

