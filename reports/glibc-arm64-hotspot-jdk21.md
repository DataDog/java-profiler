---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 07:59:45 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1789991744 45
1789991749 45
1789991754 45
1789991759 45
1789991764 42
1789991769 42
1789991774 42
1789991780 42
1789991785 42
1789991790 42
1789991795 42
1789991800 42
1789991805 43
1789991810 43
1789991815 44
1789991820 44
1789991825 45
1789991830 45
1789991835 45
1789991840 45
```
</details>

---

