---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 09:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 52-88 cores)</summary>

```
1790084796 64
1790084801 64
1790084806 64
1790084811 64
1790084816 64
1790084821 64
1790084826 64
1790084831 64
1790084836 64
1790084841 64
1790084846 64
1790084851 64
1790084856 64
1790084861 64
1790084866 64
1790084871 64
1790084876 64
1790084881 88
1790084886 88
1790084891 52
```
</details>

---

