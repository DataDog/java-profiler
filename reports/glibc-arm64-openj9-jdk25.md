---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 15:46:06 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776973251 64
1776973257 64
1776973262 64
1776973267 64
1776973272 64
1776973277 64
1776973282 64
1776973287 64
1776973292 64
1776973297 64
1776973302 64
1776973307 64
1776973312 64
1776973317 64
1776973322 64
1776973327 64
1776973332 64
1776973337 64
1776973342 64
1776973347 64
```
</details>

---

