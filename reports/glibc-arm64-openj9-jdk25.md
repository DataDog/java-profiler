---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 11:36:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776266711 64
1776266716 64
1776266722 64
1776266727 64
1776266732 64
1776266737 64
1776266742 64
1776266747 64
1776266752 64
1776266757 64
1776266762 64
1776266767 60
1776266772 60
1776266777 60
1776266782 60
1776266787 60
1776266792 60
1776266797 60
1776266802 60
1776266807 60
```
</details>

---

