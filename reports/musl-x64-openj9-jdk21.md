---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 54-67 cores)</summary>

```
1776282654 54
1776282659 54
1776282664 54
1776282669 54
1776282674 54
1776282679 54
1776282684 54
1776282689 54
1776282694 54
1776282699 63
1776282704 63
1776282709 63
1776282714 63
1776282719 61
1776282724 61
1776282729 61
1776282734 61
1776282739 61
1776282744 61
1776282749 61
```
</details>

---

