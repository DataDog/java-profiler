---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:21:06 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 8 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794323782 41
1794323787 41
1794323792 41
1794323797 41
1794323802 41
1794323807 41
1794323812 41
1794323817 41
1794323822 41
1794323827 41
1794323832 41
1794323837 46
1794323842 46
1794323847 46
1794323852 46
1794323857 46
1794323862 46
1794323867 46
1794323872 46
1794323877 46
```
</details>

---

