---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 05:53:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 14 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1776937746 32
1776937751 32
1776937756 32
1776937761 32
1776937766 32
1776937771 32
1776937776 32
1776937781 32
1776937786 32
1776937791 32
1776937796 32
1776937801 32
1776937806 32
1776937811 32
1776937816 32
1776937821 32
1776937826 32
1776937831 32
1776937836 32
1776937841 32
```
</details>

---

