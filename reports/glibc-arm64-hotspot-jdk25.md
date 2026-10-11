---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-11 01:02:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1791694744 18
1791694749 18
1791694754 18
1791694759 18
1791694764 18
1791694769 18
1791694774 18
1791694779 18
1791694784 18
1791694789 18
1791694794 18
1791694799 18
1791694804 18
1791694809 13
1791694814 13
1791694819 13
1791694824 13
1791694829 13
1791694834 13
1791694839 13
```
</details>

---

