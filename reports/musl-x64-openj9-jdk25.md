---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 13:55:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 37-44 cores)</summary>

```
1776966683 37
1776966688 37
1776966693 37
1776966698 39
1776966703 39
1776966708 39
1776966713 39
1776966718 40
1776966723 40
1776966728 40
1776966733 40
1776966738 42
1776966743 42
1776966748 42
1776966753 42
1776966758 42
1776966763 42
1776966768 42
1776966773 40
1776966778 40
```
</details>

---

