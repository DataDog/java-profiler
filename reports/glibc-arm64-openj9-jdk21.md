---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 06:54:10 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791456644 43
1791456649 43
1791456654 43
1791456659 43
1791456664 43
1791456669 43
1791456674 43
1791456679 43
1791456684 43
1791456689 43
1791456694 48
1791456699 48
1791456704 48
1791456709 48
1791456714 48
1791456719 48
1791456724 48
1791456729 48
1791456734 48
1791456739 48
```
</details>

---

