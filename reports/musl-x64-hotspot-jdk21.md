---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 14:59:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1793040889 88
1793040894 88
1793040899 90
1793040904 90
1793040909 90
1793040914 90
1793040919 90
1793040924 90
1793040929 90
1793040934 90
1793040939 90
1793040944 90
1793040949 90
1793040954 90
1793040959 90
1793040964 90
1793040969 90
1793040974 88
1793040979 88
1793040984 88
```
</details>

---

