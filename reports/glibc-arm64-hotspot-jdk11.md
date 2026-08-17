---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:06:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786971669 59
1786971674 59
1786971679 59
1786971684 59
1786971689 59
1786971694 59
1786971699 59
1786971704 59
1786971709 59
1786971714 59
1786971719 59
1786971724 59
1786971729 59
1786971734 59
1786971739 59
1786971744 59
1786971749 64
1786971754 64
1786971759 64
1786971764 64
```
</details>

---

