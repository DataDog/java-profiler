---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-14 14:58:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (7 unique values: 55-78 cores)</summary>

```
1776192782 61
1776192787 61
1776192792 63
1776192797 63
1776192802 63
1776192807 63
1776192812 63
1776192817 63
1776192822 59
1776192827 59
1776192832 59
1776192837 59
1776192842 55
1776192847 55
1776192852 55
1776192857 60
1776192862 60
1776192867 60
1776192872 60
1776192877 60
```
</details>

---

