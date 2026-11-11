---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:46:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 120 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794393767 46
1794393772 46
1794393777 46
1794393782 51
1794393787 51
1794393792 51
1794393797 51
1794393802 51
1794393807 51
1794393812 51
1794393817 51
1794393822 51
1794393827 51
1794393832 51
1794393837 51
1794393842 51
1794393847 51
1794393852 51
1794393857 51
1794393862 51
```
</details>

---

