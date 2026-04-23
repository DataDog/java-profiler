---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 03:58:19 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776930832 64
1776930837 64
1776930842 64
1776930847 64
1776930852 64
1776930857 64
1776930862 64
1776930867 64
1776930872 64
1776930877 64
1776930882 64
1776930887 64
1776930892 64
1776930897 64
1776930902 64
1776930907 64
1776930912 64
1776930917 64
1776930922 64
1776930927 64
```
</details>

---

