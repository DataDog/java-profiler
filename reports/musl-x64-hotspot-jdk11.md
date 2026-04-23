---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 14:32:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 42-45 cores)</summary>

```
1776968869 42
1776968874 42
1776968879 42
1776968884 42
1776968889 42
1776968894 42
1776968899 42
1776968904 42
1776968909 42
1776968914 42
1776968919 42
1776968924 42
1776968930 42
1776968935 42
1776968940 42
1776968945 42
1776968950 42
1776968955 42
1776968960 45
1776968965 45
```
</details>

---

