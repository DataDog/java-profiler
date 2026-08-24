---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 05:50:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 11 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787564724 48
1787564729 48
1787564734 47
1787564739 47
1787564744 47
1787564749 47
1787564754 47
1787564759 47
1787564764 48
1787564769 48
1787564774 48
1787564779 48
1787564784 48
1787564789 48
1787564794 48
1787564799 48
1787564804 48
1787564809 48
1787564814 48
1787564819 48
```
</details>

---

