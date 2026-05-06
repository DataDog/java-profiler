---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:10:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
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
1778090829 64
1778090834 64
1778090839 64
1778090844 64
```
</details>

---

