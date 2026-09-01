---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:28:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 13 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (4 unique values: 24-52 cores)</summary>

```
1788279674 24
1788279679 24
1788279684 24
1788279689 24
1788279694 24
1788279699 25
1788279704 25
1788279709 25
1788279714 25
1788279719 25
1788279724 25
1788279729 25
1788279734 25
1788279739 34
1788279744 34
1788279749 34
1788279754 34
1788279759 34
1788279764 52
1788279769 52
```
</details>

---

