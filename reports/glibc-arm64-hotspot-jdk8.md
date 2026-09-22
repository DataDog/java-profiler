---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 09:50:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-48 cores)</summary>

```
1790084766 10
1790084771 10
1790084776 10
1790084781 10
1790084786 10
1790084791 10
1790084796 10
1790084801 10
1790084806 10
1790084811 10
1790084816 10
1790084821 10
1790084826 10
1790084831 10
1790084836 10
1790084841 10
1790084846 10
1790084851 10
1790084856 48
1790084861 48
```
</details>

---

