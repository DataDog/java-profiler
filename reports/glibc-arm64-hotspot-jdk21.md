---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:47:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (5 unique values: 39-48 cores)</summary>

```
1789731774 39
1789731779 39
1789731784 42
1789731789 42
1789731794 42
1789731799 42
1789731804 42
1789731809 42
1789731814 42
1789731819 42
1789731824 42
1789731829 42
1789731834 42
1789731839 42
1789731844 42
1789731849 42
1789731854 42
1789731859 44
1789731864 44
1789731869 48
```
</details>

---

