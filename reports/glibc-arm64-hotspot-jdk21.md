---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:10:43 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778090729 62
1778090734 62
1778090739 62
1778090744 64
1778090749 64
1778090754 64
1778090759 64
1778090764 64
1778090769 64
1778090774 64
1778090779 64
1778090784 64
1778090789 64
1778090794 64
1778090799 64
1778090804 64
1778090809 64
1778090814 64
1778090819 64
1778090824 64
```
</details>

---

