---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:03:17 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1776970751 32
1776970756 32
1776970761 32
1776970766 32
1776970771 32
1776970776 32
1776970781 32
1776970786 32
1776970791 32
1776970796 32
1776970801 32
1776970806 32
1776970811 32
1776970816 32
1776970821 32
1776970826 32
1776970831 32
1776970836 32
1776970841 32
1776970846 32
```
</details>

---

