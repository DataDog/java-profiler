---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 10:22:22 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794323812 51
1794323817 46
1794323822 46
1794323827 46
1794323832 46
1794323837 46
1794323842 46
1794323847 46
1794323852 46
1794323857 46
1794323862 46
1794323867 46
1794323872 46
1794323877 51
1794323882 51
1794323887 51
1794323892 51
1794323897 51
1794323902 51
1794323907 51
```
</details>

---

