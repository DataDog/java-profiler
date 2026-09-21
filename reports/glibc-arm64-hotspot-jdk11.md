---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:40:54 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 10 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 22-49 cores)</summary>

```
1789997742 40
1789997747 22
1789997752 22
1789997757 22
1789997762 22
1789997767 22
1789997772 22
1789997777 22
1789997782 22
1789997787 22
1789997792 22
1789997797 22
1789997802 22
1789997807 31
1789997812 31
1789997817 31
1789997822 31
1789997827 31
1789997832 31
1789997837 49
```
</details>

---

