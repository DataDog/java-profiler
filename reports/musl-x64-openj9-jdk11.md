---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:39:26 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1792686779 81
1792686784 81
1792686789 81
1792686794 81
1792686799 81
1792686804 81
1792686809 81
1792686814 81
1792686819 81
1792686824 81
1792686829 81
1792686834 81
1792686839 81
1792686844 81
1792686849 81
1792686854 81
1792686859 83
1792686864 83
1792686869 83
1792686874 83
```
</details>

---

