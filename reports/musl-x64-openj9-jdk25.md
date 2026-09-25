---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 08:26:21 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 45-68 cores)</summary>

```
1790338694 45
1790338699 68
1790338704 68
1790338709 68
1790338714 68
1790338719 68
1790338724 68
1790338729 68
1790338734 68
1790338739 45
1790338744 45
1790338749 45
1790338754 45
1790338759 45
1790338764 45
1790338769 45
1790338774 45
1790338779 45
1790338784 45
1790338789 45
```
</details>

---

