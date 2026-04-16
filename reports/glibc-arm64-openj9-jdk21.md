---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 10:55:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776350972 64
1776350977 64
1776350982 64
1776350987 64
1776350992 64
1776350997 64
1776351002 64
1776351007 64
1776351012 64
1776351017 64
1776351022 64
1776351027 64
1776351032 64
1776351037 64
1776351042 64
1776351047 64
1776351052 64
1776351057 64
1776351062 64
1776351067 64
```
</details>

---

