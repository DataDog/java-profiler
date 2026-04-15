---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:36:11 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 9 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 52-60 cores)</summary>

```
1776266712 60
1776266717 60
1776266722 60
1776266727 60
1776266732 60
1776266737 60
1776266742 56
1776266747 56
1776266752 52
1776266757 52
1776266762 52
1776266767 52
1776266772 52
1776266777 52
1776266782 52
1776266787 52
1776266792 52
1776266797 52
1776266802 52
1776266807 52
```
</details>

---

