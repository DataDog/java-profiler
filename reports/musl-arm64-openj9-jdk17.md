---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:46:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794393762 43
1794393767 48
1794393772 48
1794393777 48
1794393782 48
1794393787 48
1794393792 48
1794393797 48
1794393802 48
1794393807 48
1794393812 48
1794393817 48
1794393822 48
1794393827 48
1794393832 48
1794393837 48
1794393842 48
1794393847 48
1794393852 48
1794393857 48
```
</details>

---

