---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 10:55:30 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 14 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776350974 64
1776350979 64
1776350984 64
1776350989 64
1776350994 64
1776350999 64
1776351004 64
1776351009 64
1776351014 64
1776351019 64
1776351024 64
1776351029 64
1776351034 64
1776351039 64
1776351044 64
1776351049 64
1776351054 64
1776351059 64
1776351064 64
1776351069 64
```
</details>

---

