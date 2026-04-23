---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-23 10:04:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1776952738 32
1776952743 32
1776952748 32
1776952753 32
1776952758 32
1776952763 32
1776952768 32
1776952773 32
1776952778 32
1776952783 32
1776952788 32
1776952793 32
1776952798 32
1776952803 32
1776952808 32
1776952813 32
1776952818 32
1776952823 32
1776952828 32
1776952833 32
```
</details>

---

