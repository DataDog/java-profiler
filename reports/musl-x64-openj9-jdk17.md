---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-21 06:58:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1776768694 48
1776768699 48
1776768704 48
1776768709 48
1776768714 48
1776768719 48
1776768724 48
1776768729 48
1776768734 51
1776768739 51
1776768744 51
1776768749 51
1776768755 46
1776768760 46
1776768765 46
1776768770 46
1776768775 46
1776768780 46
1776768785 46
1776768790 46
```
</details>

---

