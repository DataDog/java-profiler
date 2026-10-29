---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 17:38:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 7 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793309716 39
1793309721 39
1793309726 51
1793309731 51
1793309736 51
1793309741 51
1793309746 51
1793309751 51
1793309756 51
1793309761 51
1793309766 51
1793309771 51
1793309776 46
1793309781 46
1793309786 46
1793309791 46
1793309796 46
1793309801 46
1793309806 46
1793309811 46
```
</details>

---

