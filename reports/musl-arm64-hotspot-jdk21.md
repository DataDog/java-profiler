---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 11:03:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 11 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1787669824 52
1787669829 52
1787669834 52
1787669839 52
1787669844 52
1787669849 52
1787669854 52
1787669859 52
1787669864 47
1787669869 47
1787669874 47
1787669879 47
1787669884 47
1787669889 47
1787669894 47
1787669899 47
1787669904 47
1787669910 47
1787669915 52
1787669920 52
```
</details>

---

