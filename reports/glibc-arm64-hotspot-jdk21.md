---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-03 14:43:04 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 12 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788460704 48
1788460709 48
1788460714 48
1788460719 48
1788460724 48
1788460729 48
1788460734 48
1788460739 48
1788460744 48
1788460749 48
1788460754 48
1788460759 48
1788460764 48
1788460769 48
1788460774 43
1788460779 43
1788460784 43
1788460789 43
1788460794 43
1788460799 43
```
</details>

---

