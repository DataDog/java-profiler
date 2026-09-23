---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1166 |
| Sample Rate | 19.43/sec |
| Health Score | 1214% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 59-62 cores)</summary>

```
1790168718 61
1790168723 61
1790168728 61
1790168733 61
1790168738 61
1790168743 61
1790168748 59
1790168753 59
1790168758 59
1790168763 59
1790168768 59
1790168773 59
1790168778 59
1790168783 61
1790168788 61
1790168793 62
1790168798 62
1790168803 62
1790168808 62
1790168813 62
```
</details>

---

