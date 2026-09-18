---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:28:23 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1789712677 24
1789712682 24
1789712687 24
1789712692 24
1789712697 29
1789712702 29
1789712707 29
1789712712 29
1789712717 29
1789712722 29
1789712727 29
1789712732 29
1789712737 29
1789712743 29
1789712748 29
1789712753 29
1789712758 29
1789712763 29
1789712768 34
1789712773 34
```
</details>

---

