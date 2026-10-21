---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 01:05:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792558746 94
1792558751 94
1792558756 94
1792558761 94
1792558766 96
1792558771 96
1792558776 96
1792558781 96
1792558786 96
1792558791 96
1792558796 96
1792558801 96
1792558806 96
1792558811 96
1792558816 96
1792558821 96
1792558826 96
1792558831 96
1792558836 96
1792558841 96
```
</details>

---

