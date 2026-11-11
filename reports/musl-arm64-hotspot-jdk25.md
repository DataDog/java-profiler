---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:46:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 43-46 cores)</summary>

```
1794393772 45
1794393777 45
1794393782 45
1794393787 45
1794393792 45
1794393797 45
1794393802 45
1794393807 45
1794393812 45
1794393817 45
1794393822 43
1794393827 43
1794393832 43
1794393837 43
1794393842 43
1794393847 43
1794393852 43
1794393858 43
1794393863 43
1794393868 43
```
</details>

---

