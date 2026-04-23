---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 14:32:12 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 12 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776968764 62
1776968769 64
1776968774 64
1776968779 64
1776968784 64
1776968789 64
1776968794 64
1776968799 64
1776968804 64
1776968809 64
1776968814 64
1776968819 64
1776968824 64
1776968829 64
1776968834 64
1776968839 64
1776968844 64
1776968849 64
1776968854 64
1776968859 64
```
</details>

---

